#include "CustomScene.h"

#include "Engine/GameFramework/GameFramework.h"
#include "Engine/GameFramework/Drawer.h"
#include "Engine/GameFramework/InputManager.h"

#include "Game/GameObject/MapManager.h"
#include "Game/GameObject/Player.h"

#include "resource.h"

using Elysia::Game::CustomScene;

CustomScene::CustomScene(const tstring& _name, int _sceneIdx)
	: Scene(_name, _sceneIdx)
{
}

CustomScene::~CustomScene()
{
}

void CustomScene::Load()
{
	Scene::Load();


	Engine::GameFramework::GetInstance().GetDrawer().LoadAll(
		{ IDB_WALL, IDB_PACKAGE, IDB_MAN_FRONT, IDB_GOAL_EMPTY, IDB_GOAL_FILLED, IDB_CLEAR }
	);

	mapManager = AddGameObject<MapManager>(TEXT("MapManager"));
	player = AddGameObject<Player>(TEXT("Player"));

	Engine::GameFramework::GetInstance().GetInputManager().RegisterKey(this, VK_SPACE, &CustomScene::loadNextScene);
}

void CustomScene::Unload()
{
	Scene::Unload();

}

void CustomScene::ImportMap(const MapData& mapData)
{
	if (mapManager == nullptr || player == nullptr)
	{
		return;
	}

	mapManager->SetMapData(mapData);

	std::vector<Int2> playerPoses = mapManager->GetPoses(MapInfo::Start);
	assert(playerPoses.size() == 1);

	player->SetPosition(playerPoses[0]);
}

void CustomScene::loadNextScene()
{
	if (mapManager != nullptr && mapManager->IsCleared())
	{
		Engine::GameFramework::GetInstance().LoadSceneByName(TEXT("MapMakerScene"));
	}
}
