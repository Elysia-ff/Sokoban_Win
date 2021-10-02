#pragma once

#include "GameFramework.h"

#include <type_traits>

template <typename T>
void Elysia::Engine::GameFramework::addScene(const tstring& sceneName)
{
	static_assert(std::is_base_of_v<Scene, T>, "Type T must be inherited from Scene");

	int idx = static_cast<int>(scenes.size());
	T* scene = new T(sceneName, idx);
	scenes.push_back(static_cast<Scene*>(scene));
}
