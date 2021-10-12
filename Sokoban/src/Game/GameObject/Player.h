#pragma once

#include "Game/GameObject/MapObject.h"

namespace Elysia::Game
{
class MapManager;

class Player : public MapObject
{
	DECLARE_TYPENAME(Player);

public:
	Player(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene);

	virtual ~Player() override;

private:
	void moveUp();

	void moveDown();

	void moveRight();

	void moveLeft();

private:
	Engine::Ptr<MapManager> mapManager;
};
} // namespace Elysia::Game
