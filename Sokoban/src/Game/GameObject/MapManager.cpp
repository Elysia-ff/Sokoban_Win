#include "MapManager.h"

#include <cassert>

#include "Engine/Component/ImageComponent.h"

#include "Game/GameObject/Package.h"
#include "Game/GameObject/Goal.h"
#include "Game/GameObject/ClearImg.h"

#include "resource.h"

using Elysia::Game::MapManager;

MapManager::MapManager(const tstring& _name, unsigned int _instanceID, Engine::Scene& scene)
	: GameObject(_name, _instanceID, scene)
	, isCleared(false)
	, mapWidth(0)
	, mapHeight(0)
{
}

MapManager::~MapManager()
{
}

void MapManager::SetMapData(const MapData& newMapData)
{
	clearData();

	mapData = newMapData;

	mapHeight = static_cast<int>(mapData.size());
	for (size_t y = 0; y < mapData.size(); y++)
	{
		for (size_t x = 0; x < mapData[y].size(); x++)
		{
			if (mapWidth < mapData[y].size())
			{
				mapWidth = static_cast<int>(mapData[y].size());
			}

			Int2 pos = MakeInt2(x, y);
			if (Is(MapInfo::Wall, pos))
			{
				tstring componentName = TEXT("image_") + to_tstring(x) + TEXT("_") + to_tstring(y);
				Engine::ImageComponent& image = AddComponent<Engine::ImageComponent>(componentName);
				image.SetPosition(MakeInt2(x * UNIT_PIXEL, y * UNIT_PIXEL));
				image.SetImage(IDB_WALL);
			}
			else if (Is(MapInfo::Pack, pos))
			{
				tstring objectName = TEXT("package_") + to_tstring(packages.size());
				Package& package = AddGameObject<Package>(objectName);
				package.SetPosition(pos);
				packages.push_back(package);
			}
			else if (Is(MapInfo::Goal, pos))
			{
				tstring objectName = TEXT("goal_") + to_tstring(goals.size());
				Goal& goal = AddGameObject<Goal>(objectName);
				goal.SetPosition(pos);
				goals.push_back(goal);
			}
		}
	}
}

bool MapManager::Is(MapInfo mapInfo, Int2 pos) const
{
	assert(0 <= pos.y && pos.y < mapData.size());
	assert(0 <= pos.x && pos.x < mapData[pos.y].size());

	return mapData[pos.y][pos.x] == static_cast<char>(mapInfo);
}

bool MapManager::IsPackagePos(Int2 pos) const
{
	for (const Engine::Ptr<Package>& p : packages)
	{
		if (p != nullptr && p->GetPosition() == pos)
		{
			return true;
		}
	}

	return false;
}

bool MapManager::GetPackagePos(Int2 pos, Engine::Ptr<Package>* output) const
{
	for (const Engine::Ptr<Package>& p : packages)
	{
		if (p != nullptr && p->GetPosition() == pos)
		{
			*output = p;
			return true;
		}
	}

	return false;
}

std::vector<Int2> MapManager::GetPoses(MapInfo mapInfo) const
{
	std::vector<Int2> result;
	for (size_t y = 0; y < mapData.size(); y++)
	{
		for (size_t x = 0; x < mapData[y].size(); x++)
		{
			Int2 pos = MakeInt2(x, y);
			if (Is(mapInfo, pos))
			{
				result.push_back(pos);
			}
		}
	}

	return result;
}

void MapManager::OnPackageMoved(Package& movedPackage, Int2 prevPos)
{
	int filledGoalsCount = 0;
	for (Engine::Ptr<Goal>& goal : goals)
	{
		if (goal->GetPosition() == prevPos)
		{
			goal->SetAsEmpty();
			movedPackage.SetActive(true);
		}
		else if (goal->GetPosition() == movedPackage.GetPosition())
		{
			goal->SetAsFilled();
			movedPackage.SetActive(false);
		}

		if (goal->IsFilled())
		{
			filledGoalsCount++;
		}
	}

	if (filledGoalsCount == goals.size())
	{
		isCleared = true;

		ClearImg& obj = AddGameObject<ClearImg>(TEXT("clearImg"));
		obj.MoveToCenter(mapWidth, mapHeight);
	}
}

bool MapManager::IsCleared() const
{
	return isCleared;
}

void MapManager::clearData()
{
	for (auto iter = mapData.begin(); iter != mapData.end(); ++iter)
	{
		iter->clear();
	}
	mapData.clear();
	mapWidth = 0;
	mapHeight = 0;

	packages.clear();
	goals.clear();
}
