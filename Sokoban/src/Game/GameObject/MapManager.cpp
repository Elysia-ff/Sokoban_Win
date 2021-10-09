#include "MapManager.h"

#include <cassert>

#include "Engine/Component/ImageComponent.h"

#include "resource.h"

using Elysia::Game::MapManager;

MapManager::MapManager(const tstring& _name, unsigned int _instanceID, Engine::Scene& scene)
	: GameObject(_name, _instanceID, scene)
{
}

MapManager::~MapManager()
{
}

void MapManager::SetMapData(const MapData& newMapData)
{
	clear();

	mapData = newMapData;

	for (size_t y = 0; y < mapData.size(); y++)
	{
		for (size_t x = 0; x < mapData[y].size(); x++)
		{
			if (Is(MapInfo::Wall, MakeInt2(x, y)))
			{
				tstring componentName = TEXT("image_") + to_tstring(x) + TEXT("_") + to_tstring(y);
				Engine::ImageComponent& image = AddComponent<Engine::ImageComponent>(componentName);
				image.SetPosition(MakeInt2(x * UNIT_PIXEL, y * UNIT_PIXEL));
				image.SetImage(IDB_WALL);
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

void MapManager::clear()
{
	for (auto iter = mapData.begin(); iter != mapData.end(); ++iter)
	{
		iter->clear();
	}
	mapData.clear();
}
