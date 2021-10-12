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
class Package;
class Goal;

using MapData = std::vector<std::vector<char>>;

class MapManager : public Engine::GameObject
{
	DECLARE_TYPENAME(MapManager);

public:
	MapManager(const tstring& _name, unsigned int _instanceID, Engine::Scene& scene);

	virtual ~MapManager() override;

	void SetMapData(const MapData& newMapData);

	bool Is(MapInfo mapInfo, Int2 pos) const;

	bool IsPackagePos(Int2 pos) const;

	bool GetPackagePos(Int2 pos, Engine::Ptr<Package>* output) const;

	std::vector<Int2> GetPoses(MapInfo mapInfo) const;

	void OnPackageMoved(Package& movedPackage, Int2 prevPos);

private:
	void clearData();

private:
	MapData mapData;

	std::vector<Engine::Ptr<Package>> packages;

	std::vector<Engine::Ptr<Goal>> goals;
};
} // namespace Elysia::Game
