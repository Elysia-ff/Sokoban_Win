#include "Game/GameObject/Package.h"

#include "Engine/Component/ImageComponent.h"

#include "resource.h"

using Elysia::Game::Package;

Package::Package(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene)
	: MapObject(_name, _instanceID, _scene)
{
	image->SetImage(IDB_PACKAGE);
}

Package::~Package()
{
}
