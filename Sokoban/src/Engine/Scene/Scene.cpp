#include "Scene.h"

#include "Engine/GameFramework/GameFramework.h"
#include "Engine/GameFramework/Drawer.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Component/Component.h"

using Elysia::Engine::Scene;

Scene::Scene(const tstring& _name, int _sceneIdx)
	: Object(_name)
	, sceneIdx(_sceneIdx)
	, newInstanceID(0)
{
}

Scene::~Scene()
{
}

int Scene::GetSceneIdx() const
{
	return sceneIdx;
}

void Scene::Load()
{
	newInstanceID = 0;
}

void Scene::Unload()
{
	for (GameObject* v : gameObjects)
	{
		delete v;
	}
	std::vector<GameObject*>().swap(gameObjects);

	for (auto& kv : components)
	{
		for (Component* c : kv.second)
		{
			delete c;
		}
	}
	std::unordered_map<unsigned int, std::vector<Component*>>().swap(components);

	GameFramework::GetInstance()->GetDrawer().UnloadAll();
}

void Scene::OnPaint() const
{
	for (const auto& kv : components)
	{
		for (Component* c : kv.second)
		{
			c->OnPaint();
		}
	}
}

auto Scene::findComponent(unsigned int instanceID, const tstring& componentName) const -> Component*
{
	auto iter = components.find(instanceID);
	if (iter != components.end())
	{
		for (Component* c : iter->second)
		{
			if (c->GetName() == componentName)
			{
				return c;
			}
		}
	}

	return nullptr;
}
