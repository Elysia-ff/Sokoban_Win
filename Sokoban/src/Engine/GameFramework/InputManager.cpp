#include "InputManager.h"

#include "Engine/GameFramework/GameFramework.h"

using Elysia::Engine::InputManager;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Clear()
{
	keyBinds.clear();
}

void InputManager::OnKeyDown(WPARAM key) const
{
	auto iter = keyBinds.find(key);
	if (iter != keyBinds.end())
	{
		const std::vector<std::function<void()>>& v = iter->second;
		for (const std::function<void()>& f : v)
		{
			f();
		}

		GameFramework::GetInstance().Repaint();
	}
}
