#include "Pointer.h"

#include "Engine/Component/ImageComponent.h"

#include "resource.h"

using Elysia::Game::Pointer;

Pointer::Pointer(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene)
	: GameObject(_name, _instanceID, _scene)
	, isPressed(false)
{
	image = AddComponent<Engine::ImageComponent>(TEXT("Image"));
	image->SetImage(IDB_WALL);
}

Pointer::~Pointer()
{
}
