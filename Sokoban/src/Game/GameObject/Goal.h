#pragma once

#include "Game/GameObject/MapObject.h"

namespace Elysia::Game
{
class Goal : public MapObject
{
	DECLARE_TYPENAME(Goal);

public:
	Goal(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene);

	virtual ~Goal() override;

	void SetAsEmpty();

	void SetAsFilled();
};
} // Elysia::Game