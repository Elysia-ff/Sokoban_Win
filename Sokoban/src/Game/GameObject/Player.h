#pragma once

#include <stack>

#include "Game/GameObject/MapObject.h"

namespace Elysia::Game
{
class MapManager;

class Player : public MapObject
{
private:
	struct Record
	{
		Int2 input;
		bool bPush;
	};

	DECLARE_TYPENAME(Player);

public:
	Player(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene);

	virtual ~Player() override;

private:
	void moveUp();

	void moveDown();

	void moveRight();

	void moveLeft();

	void moveBy(Int2 input);

	void undo();

private:
	Engine::Ptr<MapManager> mapManager;

	std::stack<Record> prevInputs;
};
} // namespace Elysia::Game
