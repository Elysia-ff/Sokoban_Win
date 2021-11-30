#include "Level_2.h"

#include "Engine/GameFramework/GameFramework.h"
#include "Engine/GameFramework/Drawer.h"
#include "Engine/GameFramework/InputManager.h"

#include "Game/GameObject/MapManager.h"
#include "Game/GameObject/Player.h"

#include "resource.h"

using Elysia::Game::Level_2;

Level_2::Level_2(const tstring& _name, int _sceneIdx)
	: Scene(_name, _sceneIdx)
{
}

Level_2::~Level_2()
{
}

void Level_2::Load()
{
	Scene::Load();

	Engine::GameFramework::GetInstance().GetDrawer().LoadAll(
		{ IDB_WALL, IDB_PACKAGE, IDB_MAN_FRONT, IDB_GOAL_EMPTY, IDB_GOAL_FILLED, IDB_CLEAR }
	);

	mapManager = AddGameObject<MapManager>(TEXT("MapManager"));
	mapManager->SetMapData(
		{
			{ 'x', 'x', 'x', 'x', 'x', ' ', ' ', ' ', ' ' },
			{ 'x', 'p', ' ', ' ', 'x', ' ', ' ', ' ', ' ' },
			{ 'x', ' ', 'o', 'o', 'x', ' ', 'x', 'x', 'x' },
			{ 'x', ' ', 'o', ' ', 'x', ' ', 'x', '#', 'x' },
			{ 'x', 'x', 'x', ' ', 'x', 'x', 'x', '#', 'x' },
			{ ' ', 'x', 'x', ' ', ' ', ' ', ' ', '#', 'x' },
			{ ' ', 'x', ' ', ' ', ' ', 'x', ' ', ' ', 'x' },
			{ ' ', 'x', ' ', ' ', ' ', 'x', 'x', 'x', 'x' },
			{ ' ', 'x', 'x', 'x', 'x', 'x', ' ', ' ', ' ' }
		});

	std::vector<Int2> playerPoses = mapManager->GetPoses(MapInfo::Start);
	assert(playerPoses.size() == 1);
	Player& player = AddGameObject<Player>(TEXT("Player"));
	player.SetPosition(playerPoses[0]);

	Engine::GameFramework::GetInstance().GetInputManager().RegisterKey(this, VK_SPACE, &Level_2::loadNextScene);
}

void Level_2::Unload()
{
	Scene::Unload();
}

void Level_2::loadNextScene()
{
	if (mapManager != nullptr && mapManager->IsCleared())
	{
		Engine::GameFramework::GetInstance().LoadSceneByIdx(0);
	}
}
