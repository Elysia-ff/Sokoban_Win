#include "GameFramework.h"

#include <cassert>

#include "Window/MainWindow.h"
#include "Engine/GameFramework/Drawer.h"
#include "Engine/GameFramework/InputManager.h"
#include "Engine/Scene/Scene.h"

#include "Game/Scene/GameScene.h"

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

GameFramework::GameFramework(const Window::MainWindow& _window)
	: window(_window)
	, drawer(new Drawer())
	, inputManager(new InputManager())
	, scenes()
	, currentSceneIdx(-1)
{
	addScene<Game::GameScene>(TEXT("GameScene"));
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