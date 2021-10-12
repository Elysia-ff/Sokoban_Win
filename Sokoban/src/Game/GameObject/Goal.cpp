#include "Game/GameObject/Goal.h"

#include "Engine/Component/ImageComponent.h"

#include "resource.h"

using Elysia::Game::Goal;

Goal::Goal(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene)
	: MapObject(_name, _instanceID, _scene)
{
	image->SetImage(IDB_GOAL_EMPTY);
}

Goal::~Goal()
{
}
