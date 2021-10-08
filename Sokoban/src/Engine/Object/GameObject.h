#pragma once

#include "Engine/Object/Object.h"

namespace Elysia::Engine
{
class Scene;

class GameObject : public Object
{
	DECLARE_TYPENAME(GameObject);

public:
	GameObject(const tstring& _name, unsigned int _instanceID, Scene& _scene);

	virtual ~GameObject() override;

	unsigned int GetInstanceID() const;

	template <typename T>
	T& AddComponent(const tstring& componentName);

	template <typename T>
	T* GetComponent(const tstring& componentName) const;

	void RemoveComponent(const tstring& componentName);

private:
	const unsigned int instanceID;

	Scene& scene;
};
}; // namespace Elysia::Engine

#include "GameObject_Templates.hpp"
