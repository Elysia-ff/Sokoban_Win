#include "MapBuilder.h"

#include "Engine/GameFramework/GameFramework.h"
#include "Engine/GameFramework/InputManager.h"
#include "Engine/Component/ImageComponent.h"

#include "Game/GameObject/Pointer.h"

#include "resource.h"

using Elysia::Game::MapBuilder;

MapBuilder::MapBuilder(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene)
	: GameObject(_name, _instanceID, _scene)
{
	Engine::GameFramework::GetInstance().GetInputManager().RegisterKey(this, VK_SPACE, &MapBuilder::exportMap);
}

MapBuilder::~MapBuilder()
{
}

void MapBuilder::AddItem(const Pointer& pointer)
{
	Int2 posInUnit = pointer.GetPosInUnit();
	
	auto iter = items.find(posInUnit);
	if (iter != items.end())
	{
		const Engine::Ptr<Engine::ImageComponent>& image = iter->second;
		if (image->GetImage() == pointer.GetImage())
		{
			return;
		}

		RemoveComponent(image->GetName());
		items.erase(iter);
	}

	tstring componentName = TEXT("image_") + to_tstring(posInUnit.x) + TEXT("_") + to_tstring(posInUnit.y);
	Engine::ImageComponent& newImage = AddComponent<Engine::ImageComponent>(componentName);
	newImage.SetImage(pointer.GetImage());
	newImage.SetPosition(pointer.GetPosition());

	items.insert({ posInUnit, newImage });
}

void MapBuilder::DeleteItem(const Pointer& pointer)
{
	Int2 posInUnit = pointer.GetPosInUnit();

	auto iter = items.find(posInUnit);
	if (iter != items.end())
	{
		const Engine::Ptr<Engine::ImageComponent>& image = iter->second;
		RemoveComponent(image->GetName());
		items.erase(iter);
	}
}

void MapBuilder::exportMap() const
{
	MapData mapData = makeMapData();

	Int2 startSpot;
	if (!findStartSpot(mapData, &startSpot))
	{
		// Only one StartSpot must exist 
	}

	std::vector<Int2> spotsToReach;
	if (!findSpotsToReach(mapData, &spotsToReach))
	{
		// Goals and Packages doesn't match 
	}

	if (!validateMapData(mapData, startSpot, spotsToReach))
	{
		// Detected unreachable spot(s)
	}


}

auto MapBuilder::makeMapData() const -> MapData
{
	MapData output;

	int width = 0;
	int height = 0;
	for (const auto& kv : items)
	{
		Int2 pos = kv.first;
		if (width < pos.x)
		{
			width = pos.x;
		}

		if (height < pos.y)
		{
			height = pos.y;
		}
	}

	width++;
	height++;

	output.reserve(height);
	for (int y = 0; y < height; y++)
	{
		output.push_back(std::vector<char>(width));

		for (int x = 0; x < width; x++)
		{
			auto itemsIter = items.find(Int2(x, y));
			if (itemsIter == items.end() || itemsIter->second == nullptr)
			{
				output[y][x] = ' ';
			}
			else
			{
				const Engine::Ptr<Engine::ImageComponent>& image = itemsIter->second;
				auto imageToMapInfoIter = imageToMapInfo.find(image->GetImage());
				assert(imageToMapInfoIter != imageToMapInfo.end());

				output[y][x] = static_cast<char>(imageToMapInfoIter->second);
			}
		}
	}

	return output;
}

bool MapBuilder::findStartSpot(const MapData& mapData, Int2* outStartSpot) const
{
	assert(outStartSpot != nullptr);

	bool bFound = false;

	for (size_t y = 0; y < mapData.size(); y++)
	{
		for (size_t x = 0; x < mapData[y].size(); x++)
		{
			if (mapData[y][x] == static_cast<char>(MapInfo::Start))
			{
				if (bFound)
				{
					return false;
				}

				*outStartSpot = MakeInt2(x, y);

				bFound = true;
			}
		}
	}

	return bFound;
}

bool MapBuilder::findSpotsToReach(const MapData& mapData, std::vector<Int2>* outSpotsToReach) const
{
	assert(outSpotsToReach != nullptr);

	int goalCount = 0;
	int packageCount = 0;

	for (size_t y = 0; y < mapData.size(); y++)
	{
		for (size_t x = 0; x < mapData[y].size(); x++)
		{
			if (mapData[y][x] == static_cast<char>(MapInfo::Goal))
			{
				outSpotsToReach->push_back(MakeInt2(x, y));
				goalCount++;
			}
			else if (mapData[y][x] == static_cast<char>(MapInfo::Pack))
			{
				outSpotsToReach->push_back(MakeInt2(x, y));
				packageCount++;
			}
		}
	}

	return goalCount == packageCount;
}

bool MapBuilder::validateMapData(const MapData& mapData, Int2 startSpot, const std::vector<Int2>& spotsToReach) const
{
	ReachedMapData reachedMapData(mapData.size());
	for (size_t y = 0; y < mapData.size(); y++)
	{
		reachedMapData[y] = std::vector<bool>(mapData[y].size(), false);
	}
	reachedMapData[startSpot.y][startSpot.x] = true;

	std::unordered_map<Int2, bool> bValidSpots;
	for (size_t i = 0; i < spotsToReach.size(); i++)
	{
		bValidSpots.insert({ spotsToReach[i], false });
	}

	std::queue<Int2> nextPoses;
	nextPoses.push(startSpot);

	while (!nextPoses.empty())
	{
		Int2 pos = nextPoses.front();
		nextPoses.pop();

		auto iter = bValidSpots.find(pos);
		if (iter != bValidSpots.end())
		{
			iter->second = true;
		}

		addToNextPoses(mapData, reachedMapData, nextPoses, Int2(pos.x + 1, pos.y));
		addToNextPoses(mapData, reachedMapData, nextPoses, Int2(pos.x - 1, pos.y));
		addToNextPoses(mapData, reachedMapData, nextPoses, Int2(pos.x, pos.y + 1));
		addToNextPoses(mapData, reachedMapData, nextPoses, Int2(pos.x, pos.y - 1));
	}

	for (const auto& kv : bValidSpots)
	{
		if (!kv.second)
		{
			return false;
		}
	}

	return true;
}

void MapBuilder::addToNextPoses(const MapData& mapData, ReachedMapData& reachedMapData, std::queue<Int2>& nextPoses, Int2 pos) const
{
	if (pos.y < 0 || pos.y >= reachedMapData.size() ||
		pos.x < 0 || pos.x >= reachedMapData[pos.y].size() ||
		reachedMapData[pos.y][pos.x] ||
		mapData[pos.y][pos.x] == static_cast<char>(MapInfo::Wall))
	{
		return;
	}

	reachedMapData[pos.y][pos.x] = true;
	nextPoses.push(pos);
}
