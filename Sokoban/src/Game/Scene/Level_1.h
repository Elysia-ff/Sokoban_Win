#pragma once

#include "Engine/Object/Ptr.h"
#include "Engine/Scene/Scene.h"

namespace Elysia::Game
{
class MapManager;

class Level_1 : public Engine::Scene
{
	DECLARE_TYPENAME(Level_1);

public:
	Level_1(const tstring& _name, int _sceneIdx);

	virtual ~Level_1() override;

	virtual void Load() override;

	virtual void Unload() override;

private:
	void loadNextScene();

private:
	Engine::Ptr<MapManager> mapManager;
};
} // namespace Elysia::Game
