#include "Player.h"

#include "Engine/GameFramework/GameFramework.h"
#include "Engine/GameFramework/InputManager.h"
#include "Engine/Component/ImageComponent.h"

#include "Game/GameObject/MapManager.h"
#include "Game/GameObject/Package.h"

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
	moveBy(Int2(0, -1));
}

void Player::moveDown()
{
	moveBy(Int2(0, 1));
}

void Player::moveRight()
{
	moveBy(Int2(1, 0));
}

void Player::moveLeft()
{
	moveBy(Int2(-1, 0));
}

void Player::moveBy(Int2 input)
{
	Int2 pos = GetPosition();
	Int2 newPos = pos + input;

	if (mapManager != nullptr)
	{
		if (mapManager->Is(MapInfo::Wall, newPos))
		{
			return;
		}

		Engine::Ptr<Package> package;
		if (mapManager->GetPackagePos(newPos, &package))
		{
			if (package->CanMove(input))
			{
				package->Push(input);
			}
			else
			{
				return;
			}
		}
	}

	SetPosition(newPos);
}
