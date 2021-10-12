#pragma once

#include "Engine/Scene/Scene.h"

namespace Elysia::Game
{
class GameScene : public Engine::Scene
{
	DECLARE_TYPENAME(GameScene);

public:
	GameScene(const tstring& _name, int _sceneIdx);

	virtual ~GameScene() override;

	virtual void Load() override;

	virtual void Unload() override;
};
} // namespace Elysia::Game
