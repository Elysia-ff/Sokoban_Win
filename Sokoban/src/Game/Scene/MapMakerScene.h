#pragma once

#include "Engine/Scene/Scene.h"

namespace Elysia::Game
{
class MapMakerScene : public Engine::Scene
{
	DECLARE_TYPENAME(MapMakerScene);

public:
	MapMakerScene(const tstring& _name, int _sceneIdx);

	virtual ~MapMakerScene() override;

	virtual void Load() override;

	virtual void Unload() override;
};
} // namespace Elysia::Game
