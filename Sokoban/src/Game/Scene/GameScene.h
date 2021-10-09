#pragma once

#include "Engine/Scene/Scene.h"
#include "Engine/Object/Ptr.h"

namespace Elysia::Game
{
class MapManager;
class Player;

class GameScene : public Engine::Scene
{
	DECLARE_TYPENAME(GameScene);

public:
	GameScene(const tstring& _name, int _sceneIdx);

	virtual ~GameScene() override;

	virtual void Load() override;

	virtual void Unload() override;

private:
	Engine::Ptr<MapManager> mapManager;

	Engine::Ptr<Player> player;
};
} // namespace Elysia::Game
