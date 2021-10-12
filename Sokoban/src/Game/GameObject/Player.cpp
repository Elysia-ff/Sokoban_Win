#include "Player.h"

#include "Engine/GameFramework/GameFramework.h"
#include "Engine/GameFramework/InputManager.h"
#include "Engine/Component/ImageComponent.h"

#include "Game/GameObject/MapManager.h"

#include "resource.h"

using Elysia::Game::Player;

Player::Player(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene)
	: MapObject(_name, _instanceID, _scene)
{
	image->SetImage(IDB_MAN_FRONT);

	mapManager = FindGameObject<MapManager>(TEXT("MapManager"));

	Engine::InputManager& inputManager = Engine::GameFramework::GetInstance().GetInputManager();
	inputManager.RegisterKey(this, VK_UP, &Player::moveUp);
	inputManager.RegisterKey(this, VK_DOWN, &Player::moveDown);
	inputManager.RegisterKey(this, VK_RIGHT, &Player::moveRight);
	inputManager.RegisterKey(this, VK_LEFT, &Player::moveLeft);
}

Player::~Player()
{
}

void Player::moveUp()
{
	Int2 pos = GetPosition();
	Int2 newPos(pos.x, pos.y - 1);
	if (mapManager != nullptr && !mapManager->Is(MapInfo::Wall, newPos))
	{
		SetPosition(newPos);
	}
}

void Player::moveDown()
{
	Int2 pos = GetPosition();
	Int2 newPos(pos.x, pos.y + 1);
	if (mapManager != nullptr && !mapManager->Is(MapInfo::Wall, newPos))
	{
		SetPosition(newPos);
	}
}

void Player::moveRight()
{
	Int2 pos = GetPosition();
	Int2 newPos(pos.x + 1, pos.y);
	if (mapManager != nullptr && !mapManager->Is(MapInfo::Wall, newPos))
	{
		SetPosition(newPos);
	}
}

void Player::moveLeft()
{
	Int2 pos = GetPosition();
	Int2 newPos(pos.x - 1, pos.y);
	if (mapManager != nullptr && !mapManager->Is(MapInfo::Wall, newPos))
	{
		SetPosition(newPos);
	}
}
