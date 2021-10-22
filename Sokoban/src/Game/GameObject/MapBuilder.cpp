#include "MapBuilder.h"

#include "Engine/Component/ImageComponent.h"

#include "Game/GameObject/Pointer.h"

using Elysia::Game::MapBuilder;

MapBuilder::MapBuilder(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene)
	: GameObject(_name, _instanceID, _scene)
{
}

MapBuilder::~MapBuilder()
{
}

void MapBuilder::AddItem(const Pointer& pointer)
{
	Int2 posInUnit = pointer.GetPosInUnit();
	
	auto iter = items.find(posInUnit);
	if (iter != items.end())
	{
		const Engine::Ptr<Engine::ImageComponent>& image = iter->second;
		if (image->GetImage() == pointer.GetImage())
		{
			return;
		}

		items.erase(iter);
	}

	tstring componentName = TEXT("image_") + to_tstring(posInUnit.x) + TEXT("_") + to_tstring(posInUnit.y);
	Engine::ImageComponent& newImage = AddComponent<Engine::ImageComponent>(componentName);
	newImage.SetImage(pointer.GetImage());
	newImage.SetPosition(pointer.GetPosition());

	items.insert({ posInUnit, newImage });
}
