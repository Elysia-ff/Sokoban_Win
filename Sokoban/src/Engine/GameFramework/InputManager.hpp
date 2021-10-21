#pragma once

#include "InputManager.h"

template <typename T, typename Func>
void Elysia::Engine::InputManager::RegisterKey(T obj, WPARAM key, Func func)
{
	std::function<void()> f = std::bind(func, obj);
	keyBinds[key].push_back(std::move(f));
}

template <typename T, typename Func>
void Elysia::Engine::InputManager::RegisterCommand(T obj, WORD cmd, Func func)
{
	std::function<void()> f = std::bind(func, obj);
	commandBinds[cmd].push_back(std::move(f));
}
