#pragma once

#include <vector>

#include "Engine/EngineCommon.h"

namespace Elysia::Window
{
class MainWindow;
}

namespace Elysia::Engine
{
class Drawer;
class InputManager;
class Scene;

class GameFramework
{
public:
	static void Allocate(const Window::MainWindow& _window);

	static GameFramework& GetInstance();

	static void Release();

private:
	inline static GameFramework* Instance = nullptr;

public:
	const Window::MainWindow& GetWindow() const;

	Drawer& GetDrawer() const;

	InputManager& GetInputManager() const;

	void LoadSceneByIdx(int idx);

	void LoadSceneByName(const tstring& sceneName);

	int GetCurrentSceneIdx() const;

	int GetSceneCount() const;

	void Repaint() const;

	void OnPaint() const;

	void OnKeyDown(WPARAM key) const;

	void OnCommand(WPARAM wParam) const;

	void OnMouse(UINT msg, LPARAM lParam) const;

private:
	GameFramework() = delete;

	GameFramework(const Window::MainWindow& _window);

	~GameFramework();

	template <typename T>
	void addScene(const tstring& sceneName);

	void unloadCurrentScene();

	void startGame();

	void loadMapBuilderScene();

private:
	const Window::MainWindow& window;

	Drawer* drawer;

	InputManager* inputManager;

	std::vector<Scene*> scenes;

	int currentSceneIdx;
};
} // namespace Elysia::Engine

#include "GameFramework_Templates.hpp"
