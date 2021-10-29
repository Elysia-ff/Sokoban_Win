#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "Engine/EngineCommon.h"

namespace Elysia::Engine
{
class InputManager
{
	DELETE_COPY(InputManager);

	DELETE_MOVE(InputManager);

public:
	InputManager();

	~InputManager();

	void Clear();

	template <typename T, typename Func>
	void RegisterKey(T obj, WPARAM key, Func func);

	void OnKeyDown(WPARAM key) const;

	template <typename T, typename Func>
	void RegisterGlobalCommand(T obj, WORD cmd, Func func);

	void OnGlobalCommand(WORD cmd) const;

	template <typename T, typename Func>
	void RegisterCommand(T obj, WORD cmd, Func func);

	void OnCommand(WORD cmd) const;

	template <typename T, typename Func>
	void RegisterMouse(T obj, UINT msg, Func func);

	void OnMouse(UINT msg, Int2 mousePosition) const;

private:
	std::unordered_map<WPARAM, std::vector<std::function<void()>>> keyBinds;

	std::unordered_map<WORD, std::vector<std::function<void()>>> globalCommandBinds;

	std::unordered_map<WORD, std::vector<std::function<void()>>> commandBinds;

	std::unordered_map<UINT, std::vector<std::function<void(Int2)>>> mouseBinds;
};
}; // namespace Elysia::Engine

#include "InputManager.hpp"
