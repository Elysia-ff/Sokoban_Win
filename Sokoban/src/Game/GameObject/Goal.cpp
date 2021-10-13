#include "Game/GameObject/Goal.h"

#include "Engine/Component/ImageComponent.h"

#include "resource.h"

using Elysia::Game::Goal;

Goal::Goal(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene)
	: MapObject(_name, _instanceID, _scene)
	, isFilled(false)
{
	SetAsEmpty();
}

Goal::~Goal()
{
}

void Goal::SetAsEmpty()
{
	image->SetImage(IDB_GOAL_EMPTY);
	isFilled = false;
}

void Goal::SetAsFilled()
{
	image->SetImage(IDB_GOAL_FILLED);
	isFilled = true;
}

bool Goal::IsFilled() const
{
	return isFilled;
}
