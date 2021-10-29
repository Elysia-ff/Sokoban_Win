#include "GameFramework.h"

#include <cassert>

#include "Window/MainWindow.h"
#include "Engine/GameFramework/Drawer.h"
#include "Engine/GameFramework/InputManager.h"
#include "Engine/Scene/Scene.h"

#include "Game/Scene/Level_1.h"
#include "Game/Scene/Level_2.h"
#include "Game/Scene/MapMakerScene.h"

#include "resource.h"

using Elysia::Engine::GameFramework;

void GameFramework::Allocate(const Window::MainWindow& _window)
{
	assert(Instance == nullptr);
	Instance = new GameFramework(_window);
}

GameFramework& GameFramework::GetInstance()
{
	assert(Instance != nullptr);

	return *Instance;
}

void GameFramework::Release()
{
	delete Instance;

	Instance = nullptr;
}

auto GameFramework::GetWindow() const -> const Window::MainWindow&
{
	return window;
}

auto GameFramework::GetDrawer() const -> Drawer&
{
	return *drawer;
}

auto GameFramework::GetInputManager() const -> InputManager&
{
	return *inputManager;
}

void GameFramework::LoadSceneByIdx(int idx)
{
	assert(0 <= idx && idx < scenes.size());

	unloadCurrentScene();

	currentSceneIdx = idx;
	scenes[currentSceneIdx]->Load();

	Repaint();
}

void GameFramework::LoadSceneByName(const tstring& sceneName)
{
	for (Scene* scene : scenes)
	{
		if (scene->GetName() == sceneName)
		{
			LoadSceneByIdx(scene->GetSceneIdx());

			return;
		}
	}

	assert(false); // unreachable
}

int GameFramework::GetCurrentSceneIdx() const
{
	return currentSceneIdx;
}

int GameFramework::GetSceneCount() const
{
	return static_cast<int>(scenes.size());
}

void GameFramework::Repaint() const
{
	InvalidateRect(window.GetHandle(), nullptr, TRUE);
}

void GameFramework::OnPaint() const
{
	if (0 <= currentSceneIdx && currentSceneIdx < scenes.size())
	{
		drawer->BeginPaint();
		scenes[currentSceneIdx]->OnPaint();
		drawer->EndPaint();
	}
}

void GameFramework::OnKeyDown(WPARAM key) const
{
	inputManager->OnKeyDown(key);
}

void GameFramework::OnCommand(WPARAM wParam) const
{
	WORD cmd = LOWORD(wParam);
	inputManager->OnGlobalCommand(cmd);
	inputManager->OnCommand(cmd);
}

void GameFramework::OnMouse(UINT msg, LPARAM lParam) const
{
	inputManager->OnMouse(msg, Int2(LOWORD(lParam), HIWORD(lParam)));
}

GameFramework::GameFramework(const Window::MainWindow& _window)
	: window(_window)
	, drawer(new Drawer())
	, inputManager(new InputManager())
	, scenes()
	, currentSceneIdx(-1)
{
	addScene<Game::Level_1>(TEXT("Level_1"));
	addScene<Game::Level_2>(TEXT("Level_2"));

	addScene<Game::MapMakerScene>(TEXT("MapMakerScene"));

	inputManager->RegisterGlobalCommand(this, ID_MENU_STARTGAME, &GameFramework::startGame);
	inputManager->RegisterGlobalCommand(this, ID_MENU_MAPBUILDER, &GameFramework::loadMapBuilderScene);
}

GameFramework::~GameFramework()
{
	unloadCurrentScene();

	delete drawer;
	delete inputManager;

	for (Scene* scene : scenes)
	{
		delete scene;
	}
}

void GameFramework::unloadCurrentScene()
{
	if (currentSceneIdx >= 0)
	{
		scenes[currentSceneIdx]->Unload();

		drawer->UnloadAll();
		inputManager->Clear();
	}
}

void GameFramework::startGame()
{
	LoadSceneByIdx(0);
}

void GameFramework::loadMapBuilderScene()
{
	int idx = static_cast<int>(scenes.size()) - 1;
	LoadSceneByIdx(idx);
}
