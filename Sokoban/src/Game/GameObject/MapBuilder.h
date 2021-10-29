#pragma once

#include <unordered_map>
#include <vector>
#include <queue>

#include "Engine/Object/GameObject.h"
#include "Engine/Object/Ptr.h"

#include "Game/GameCommon.h"

namespace Elysia::Engine
{
class ImageComponent;
}

namespace Elysia::Game
{
class Pointer;

class MapBuilder : public Engine::GameObject
{
	DECLARE_TYPENAME(MapBuilder);

public:
	MapBuilder(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene);

	virtual ~MapBuilder() override;

	void AddItem(const Pointer& pointer);

	void DeleteItem(const Pointer& pointer);

private:
	void exportMap() const;

	MapData makeMapData() const;

	bool findStartSpot(const MapData& mapData, Int2* outStartSpot) const;

	bool findSpotsToReach(const MapData& mapData, std::vector<Int2>* outSpotToReach) const;

	bool validateMapData(const MapData& mapData, Int2 startSpot, const std::vector<Int2>& spotsToReach) const;

	void addToNextPoses(const MapData& mapData, ReachedMapData& reachedMapData, std::queue<Int2>& nextPoses, Int2 pos) const;

private:
	std::unordered_map<Int2, Engine::Ptr<Engine::ImageComponent>> items;
};
} // namespace Elysia::Game
