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
class Scene;

class GameFramework
{
public:
	static void Allocate(const Window::MainWindow& _window);

	static GameFramework* GetInstance();

	static void Release();

private:
	inline static GameFramework* Instance = nullptr;

public:
	const Window::MainWindow& GetWindow() const;

	Drawer& GetDrawer() const;

	void LoadSceneByIdx(int idx);

	void LoadSceneByName(const tstring& sceneName);

	void Repaint() const;

	void OnPaint() const;

private:
	GameFramework() = delete;

	GameFramework(const Window::MainWindow& _window);

	~GameFramework();

	template <typename T>
	void addScene(const tstring& sceneName);

private:
	const Window::MainWindow& window;

	Drawer* drawer;

	std::vector<Scene*> scenes;

	int currentSceneIdx;
};
} // namespace Elysia::Engine

#include "GameFramework_Templates.hpp"
