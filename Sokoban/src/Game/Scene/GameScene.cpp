#include "GameScene.h"

#include "Engine/GameFramework/GameFramework.h"
#include "Engine/GameFramework/Drawer.h"
#include "Engine/GameFramework/InputManager.h"

#include "Game/GameObject/MapManager.h"
#include "Game/GameObject/Player.h"
#include "Game/GameObject/Package.h"
#include "Game/GameObject/Goal.h"

#include "resource.h"

using Elysia::Game::GameScene;

GameScene::GameScene(const tstring& _name, int _sceneIdx)
	: Scene(_name, _sceneIdx)
	, mapManager()
	, player()
{
}

GameScene::~GameScene()
{
}

void GameScene::Load()
{
	Scene::Load();

	Engine::GameFramework::GetInstance().GetDrawer().LoadAll(
		{ IDB_WALL, IDB_PACKAGE, IDB_MAN_FRONT, IDB_GOAL_EMPTY, IDB_GOAL_FILLED }
	);

	mapManager = AddGameObject<MapManager>(TEXT("MapManager"));
	mapManager->SetMapData(
		{
			{ ' ', ' ', 'x', 'x', 'x', ' ', ' ', ' ' },
			{ ' ', ' ', 'x', '#', 'x', ' ', ' ', ' ' },
			{ ' ', ' ', 'x', ' ', 'x', 'x', 'x', 'x' },
			{ 'x', 'x', 'x', 'o', ' ', 'o', '#', 'x' },
			{ 'x', '#', ' ', 'o', 'p', 'x', 'x', 'x' },
			{ 'x', 'x', 'x', 'x', 'o', 'x', ' ', ' ' },
			{ ' ', ' ', ' ', 'x', '#', 'x', ' ', ' ' },
			{ ' ', ' ', ' ', 'x', 'x', 'x', ' ', ' ' }
		});

	std::vector<Int2> packagePoses = mapManager->GetPoses(MapInfo::Pack);
	for (size_t i = 0; i < packagePoses.size(); i++)
	{
		Package& package = AddGameObject<Package>(TEXT("package_") + to_tstring(i));
		package.SetPosition(packagePoses[i]);
	}

	std::vector<Int2> goalPoses = mapManager->GetPoses(MapInfo::Goal);
	for (size_t i = 0; i < goalPoses.size(); i++)
	{
		Goal& goal = AddGameObject<Goal>(TEXT("goal_") + to_tstring(i));
		goal.SetPosition(goalPoses[i]);
	}

	std::vector<Int2> playerPoses = mapManager->GetPoses(MapInfo::Start);
	assert(playerPoses.size() == 1);
	player = AddGameObject<Player>(TEXT("Player"));
	player->SetPosition(playerPoses[0]);
}

void GameScene::Unload()
{
	Scene::Unload();
}
