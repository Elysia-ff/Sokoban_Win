#pragma once

#include "Engine/Object/Ptr.h"
#include "Engine/Scene/Scene.h"

#include "Game/GameCommon.h"

namespace Elysia::Game
{
class MapManager;
class Player;

class CustomScene : public Engine::Scene
{
	DECLARE_TYPENAME(CustomScene);

public:
	CustomScene(const tstring& _name, int _sceneIdx);

	virtual ~CustomScene() override;

	virtual void Load() override;

	virtual void Unload() override;

	void ImportMap(const MapData& mapData);

private:
	void loadNextScene();

private:
	Engine::Ptr<MapManager> mapManager;

	Engine::Ptr<Player> player;
};
} // namespace Elysia::Game
