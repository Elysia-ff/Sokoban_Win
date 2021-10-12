#include "Game/GameObject/MapObject.h"

#include "Engine/Component/ImageComponent.h"

#include "Game/GameCommon.h"

using Elysia::Game::MapObject;

MapObject::MapObject(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene)
	: GameObject(_name, _instanceID, _scene)
	, pos(0, 0)
{
	image = AddComponent<Engine::ImageComponent>(TEXT("image"));
}

MapObject::~MapObject()
{
}

void MapObject::SetPosition(Int2 newPos)
{
	pos = newPos;

	if (image != nullptr)
	{
		image->SetPosition(Int2(pos.x * UNIT_PIXEL, pos.y * UNIT_PIXEL));
	}
}

Int2 MapObject::GetPosition() const
{
	return pos;
}

void MapObject::SetActive(bool value)
{
	if (image != nullptr)
	{
		image->SetActive(value);
	}
}
