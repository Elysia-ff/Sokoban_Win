#include "GameScene.h"

#include "Engine/GameFramework/GameFramework.h"
#include "Engine/GameFramework/Drawer.h"
#include "Engine/Component/ImageComponent.h"
#include "Game/GameObject/SampleObject.h"
#include "resource.h"

using Elysia::Game::GameScene;

GameScene::GameScene(const tstring& _name, int _sceneIdx)
	: Scene(_name, _sceneIdx)
{
}

GameScene::~GameScene()
{
}

void GameScene::Load()
{
	Scene::Load();

	Engine::GameFramework::GetInstance()->GetDrawer().LoadAll({ IDB_SAMPLE1, IDB_SAMPLE2 });

	Engine::GameObject& obj1 = AddGameObject<Engine::GameObject>(TEXT("sample1"));
	Engine::ImageComponent& image = AddComponent<Engine::ImageComponent>(obj1.GetInstanceID(), TEXT("image"));
	image.SetPosition({ 0, 0 });
	image.SetImage(IDB_SAMPLE1);

	AddGameObject<SampleObject>(TEXT("sample2"));
}

void GameScene::Unload()
{
	Scene::Unload();
}
