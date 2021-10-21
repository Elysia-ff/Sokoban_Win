#include "MapMakerScene.h"

#include "Engine/GameFramework/GameFramework.h"
#include "Engine/GameFramework/Drawer.h"

#include "Game/GameObject/Pointer.h"

#include "resource.h"

using Elysia::Game::MapMakerScene;

MapMakerScene::MapMakerScene(const tstring& _name, int _sceneIdx)
	: Scene(_name, _sceneIdx)
{
}

MapMakerScene::~MapMakerScene()
{
}

void MapMakerScene::Load()
{
	Scene::Load();

	Engine::GameFramework::GetInstance().GetDrawer().LoadAll({ IDB_WALL });
	Pointer& pointer = AddGameObject<Pointer>(TEXT("Pointer"));
}

void MapMakerScene::Unload()
{
	Scene::Unload();
}
