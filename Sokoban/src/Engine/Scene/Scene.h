#pragma once

#include <vector>
#include <unordered_map>

#include "Engine/Object/Object.h"

namespace Elysia::Engine
{
class GameObject;
class Component;

class Scene : public Object
{
	DECLARE_TYPENAME(Scene);

public:
	Scene(const tstring& _name, int _sceneIdx);

	virtual ~Scene() override;

	int GetSceneIdx() const;

	virtual void Load();

	virtual void Unload();

	void OnPaint() const;

	template <typename T>
	T& AddGameObject(const tstring& objectName);

	template <typename T>
	T& FindGameObject(const tstring& objectName) const;

	template <typename T>
	T& AddComponent(unsigned int instanceID, const tstring& componentName);

	template <typename T>
	T* GetComponent(unsigned int instanceID, const tstring& componentName) const;

	void RemoveComponent(unsigned int instanceID, const tstring& componentName);

private:
	Component* findComponent(unsigned int instanceID, const tstring& componentName) const;

private:
	const int sceneIdx;

	unsigned int newInstanceID;

	std::vector<GameObject*> gameObjects;

	std::unordered_map<unsigned int, std::vector<Component*>> components;
};
}; // namespace Elysia::Engine

#include "Scene_Templates.hpp"
