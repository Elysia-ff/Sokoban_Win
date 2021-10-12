#pragma once

#include "Game/GameObject/MapObject.h"

namespace Elysia::Game
{
class MapManager;

class Package : public MapObject
{
	DECLARE_TYPENAME(Package);

public:
	Package(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene);

	virtual ~Package() override;

	bool CanMove(Int2 input) const;

	void Push(Int2 input);

private:
	Engine::Ptr<MapManager> mapManager;
};
} // namespace Elysia::Game
