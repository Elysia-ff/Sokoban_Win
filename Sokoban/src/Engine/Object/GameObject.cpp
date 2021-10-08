#include "GameObject.h"

using Elysia::Engine::GameObject;

GameObject::GameObject(const tstring& _name, unsigned int _instanceID, Scene& _scene)
	: Object(_name)
	, instanceID(_instanceID)
	, scene(_scene)
{
}

GameObject::~GameObject()
{
}

unsigned int GameObject::GetInstanceID() const
{
	return instanceID;
}

void GameObject::RemoveComponent(const tstring& componentName)
{
	scene.RemoveComponent(GetInstanceID(), componentName);
}
