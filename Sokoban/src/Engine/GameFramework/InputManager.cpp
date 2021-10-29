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
	commandBinds.clear();
	mouseBinds.clear();
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

void InputManager::OnGlobalCommand(WORD cmd) const
{
	auto iter = globalCommandBinds.find(cmd);
	if (iter != globalCommandBinds.end())
	{
		const std::vector<std::function<void()>>& v = iter->second;
		for (const std::function<void()>& f : v)
		{
			f();
		}
	}
}

void InputManager::OnCommand(WORD cmd) const
{
	auto iter = commandBinds.find(cmd);
	if (iter != commandBinds.end())
	{
		const std::vector<std::function<void()>>& v = iter->second;
		for (const std::function<void()>& f : v)
		{
			f();
		}
	}
}

void InputManager::OnMouse(UINT msg, Int2 mousePosition) const
{
	auto iter = mouseBinds.find(msg);
	if (iter != mouseBinds.end())
	{
		const std::vector<std::function<void(Int2)>>& v = iter->second;
		for (const std::function<void(Int2)>& f : v)
		{
			f(mousePosition);
		}

		GameFramework::GetInstance().Repaint();
	}
}
