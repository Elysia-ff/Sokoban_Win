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

private:
	std::unordered_map<WPARAM, std::vector<std::function<void()>>> keyBinds;
};
}; // namespace Elysia::Engine

#include "InputManager.hpp"
