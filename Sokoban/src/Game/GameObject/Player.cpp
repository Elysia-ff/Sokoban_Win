#include "Player.h"

#include "Engine/GameFramework/GameFramework.h"
#include "Engine/GameFramework/InputManager.h"
#include "Engine/Component/ImageComponent.h"

#include "Game/GameCommon.h"
#include "Game/GameObject/MapManager.h"

#include "resource.h"

using Elysia::Game::Player;

Player::Player(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene)
	: GameObject(_name, _instanceID, _scene)
	, pos(0, 0)
{
	mapManager = FindGameObject<MapManager>(TEXT("MapManager"));

	image = AddComponent<Engine::ImageComponent>(TEXT("Image"));
	image->SetImage(IDB_MAN_FRONT);

	Engine::InputManager& inputManager = Engine::GameFramework::GetInstance().GetInputManager();
	inputManager.RegisterKey(this, VK_UP, &Player::moveUp);
	inputManager.RegisterKey(this, VK_DOWN, &Player::moveDown);
	inputManager.RegisterKey(this, VK_RIGHT, &Player::moveRight);
	inputManager.RegisterKey(this, VK_LEFT, &Player::moveLeft);
}

Player::~Player()
{
}

void Player::SetPosition(Int2 newPos)
{
	pos = newPos;
	updateImage();
}

void Player::updateImage()
{
	if (image != nullptr)
	{
		image->SetPosition(Int2(pos.x * UNIT_PIXEL, pos.y * UNIT_PIXEL));
	}
}

void Player::moveUp()
{
	Int2 newPos(pos.x, pos.y - 1);
	if (mapManager != nullptr && !mapManager->Is(MapInfo::Wall, newPos))
	{
		pos = newPos;
		updateImage();
	}
}

void Player::moveDown()
{
	Int2 newPos(pos.x, pos.y + 1);
	if (mapManager != nullptr && !mapManager->Is(MapInfo::Wall, newPos))
	{
		pos = newPos;
		updateImage();
	}
}

void Player::moveRight()
{
	Int2 newPos(pos.x + 1, pos.y);
	if (mapManager != nullptr && !mapManager->Is(MapInfo::Wall, newPos))
	{
		pos = newPos;
		updateImage();
	}
}

void Player::moveLeft()
{
	Int2 newPos(pos.x - 1, pos.y);
	if (mapManager != nullptr && !mapManager->Is(MapInfo::Wall, newPos))
	{
		pos = newPos;
		updateImage();
	}
}
