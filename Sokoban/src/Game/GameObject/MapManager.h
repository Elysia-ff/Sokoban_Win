#pragma once

#include <vector>

#include "Engine/Object/GameObject.h"
#include "Engine/Object/Ptr.h"

#include "Game/GameCommon.h"

namespace Elysia::Engine
{
class ImageComponent;
}

namespace Elysia::Game
{
using MapData = std::vector<std::vector<char>>;

class MapManager : public Engine::GameObject
{
	DECLARE_TYPENAME(MapManager);

public:
	MapManager(const tstring& _name, unsigned int _instanceID, Engine::Scene& scene);

	virtual ~MapManager() override;

	void SetMapData(const MapData& newMapData);

	bool Is(MapInfo mapInfo, Int2 pos) const;

	std::vector<Int2> GetPoses(MapInfo mapInfo) const;

private:
	void clear();

private:
	MapData mapData;
};
} // namespace Elysia::Game
