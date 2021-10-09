#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Object/Ptr.h"

namespace Elysia::Engine
{
class ImageComponent;
}

namespace Elysia::Game
{
class MapManager;

class Player : public Engine::GameObject
{
	DECLARE_TYPENAME(Player);

public:
	Player(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene);

	virtual ~Player() override;

	void SetPosition(Int2 newPos);

private:
	void updateImage();

	void moveUp();

	void moveDown();

	void moveRight();

	void moveLeft();

private:
	Engine::Ptr<MapManager> mapManager;

	Engine::Ptr<Engine::ImageComponent> image;

	Int2 pos;
};
} // namespace Elysia::Game
