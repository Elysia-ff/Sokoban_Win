#include "Game/GameObject/Package.h"

#include "Engine/Component/ImageComponent.h"

#include "Game/GameObject/MapManager.h"

#include "resource.h"

using Elysia::Game::Package;

Package::Package(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene)
	: MapObject(_name, _instanceID, _scene)
{
	image->SetImage(IDB_PACKAGE);

	mapManager = FindGameObject<MapManager>(TEXT("MapManager"));
}

Package::~Package()
{
}

bool Package::CanMove(Int2 input) const
{
	Int2 prevPos = GetPosition();
	Int2 newPos = prevPos + input;

	return mapManager == nullptr ||
		(!mapManager->Is(MapInfo::Wall, newPos) && !mapManager->IsPackagePos(newPos));
}

void Package::Push(Int2 input)
{
	Int2 prevPos = GetPosition();
	Int2 newPos = prevPos + input;

	SetPosition(newPos);

	if (mapManager != nullptr)
	{
		mapManager->OnPackageMoved(*this, prevPos);
	}
}
