#pragma once

#include "GameObject.h"

#include "Engine/Scene/Scene.h"

template <typename T>
T& Elysia::Engine::GameObject::AddGameObject(const tstring& objectName)
{
	return scene.AddGameObject<T>(objectName);
}

template <typename T>
T& Elysia::Engine::GameObject::FindGameObject(const tstring& objectName) const
{
	return scene.FindGameObject<T>(objectName);
}

template <typename T>
T& Elysia::Engine::GameObject::AddComponent(const tstring& componentName)
{
	return scene.AddComponent<T>(GetInstanceID(), componentName);
}

template <typename T>
T* Elysia::Engine::GameObject::GetComponent(const tstring& componentName) const
{
	return scene.GetComponent<T>(GetInstanceID(), componentName);
}
