#pragma once

#include "Engine/Scene/Scene.h"

namespace Elysia::Game
{
class Level_2 : public Engine::Scene
{
	DECLARE_TYPENAME(Level_2);

public:
	Level_2(const tstring& _name, int _sceneIdx);

	virtual ~Level_2() override;

	virtual void Load() override;

	virtual void Unload() override;
};
} // namespace Elysia::Game