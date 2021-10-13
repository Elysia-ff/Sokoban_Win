#pragma once

#include "Engine/Scene/Scene.h"

namespace Elysia::Game
{
class Level_1 : public Engine::Scene
{
	DECLARE_TYPENAME(Level_1);

public:
	Level_1(const tstring& _name, int _sceneIdx);

	virtual ~Level_1() override;

	virtual void Load() override;

	virtual void Unload() override;
};
} // namespace Elysia::Game
