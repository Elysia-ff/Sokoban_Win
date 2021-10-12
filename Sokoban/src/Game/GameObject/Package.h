#pragma once

#include "Game/GameObject/MapObject.h"

namespace Elysia::Game
{
class Package : public MapObject
{
	DECLARE_TYPENAME(Package);

public:
	Package(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene);

	virtual ~Package() override;
};
} // namespace Elysia::Game
