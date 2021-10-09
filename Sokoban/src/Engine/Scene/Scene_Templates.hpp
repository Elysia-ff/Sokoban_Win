#pragma once

#include "Scene.h"

#include <cassert>
#include <type_traits>

template <typename T>
T& Elysia::Engine::Scene::AddGameObject(const tstring& objectName)
{
	static_assert(std::is_base_of_v<GameObject, T>, "Type T must be inherited from GameObject");
	assert(components.find(newInstanceID) == components.end());

	components.insert({ newInstanceID, std::vector<Component*>() });
	T* newObject = new T(objectName, newInstanceID, *this);
	gameObjects.push_back(static_cast<GameObject*>(newObject));

	newInstanceID++;

	return *newObject;
}

template <typename T>
T& Elysia::Engine::Scene::FindGameObject(const tstring& objectName) const
{
	static_assert(std::is_base_of_v<GameObject, T>, "Type T must be inherited from GameObject");
	
	for (GameObject* g : gameObjects)
	{
		if (g->GetName() == objectName)
		{
			return *dynamic_cast<T*>(g);
		}
	}

	assert(false); // unreachable
	std::terminate();
}

template <typename T>
T& Elysia::Engine::Scene::AddComponent(unsigned int instanceID, const tstring& componentName)
{
	static_assert(std::is_base_of_v<Component, T>, "Type T must be inherited from Component");
	assert(components.find(instanceID) != components.end());
	assert(findComponent(instanceID, componentName) == nullptr);

	std::vector<Component*>& list = components[instanceID];
	T* newComponent = new T(componentName);
	list.push_back(static_cast<Component*>(newComponent));

	return *newComponent;
}

template <typename T>
T* Elysia::Engine::Scene::GetComponent(unsigned int instanceID, const tstring& componentName) const
{
	static_assert(std::is_base_of_v<Component, T>, "Type T must be inherited from Component");

	Component* component = findComponent(instanceID, componentName);

	return component != nullptr ? dynamic_cast<T*>(component) : nullptr;
}
