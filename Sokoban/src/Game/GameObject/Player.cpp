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
	inputManager.RegisterKey(this, 'Z', &Player::undo);
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
	bool bPush = false;

	if (mapManager != nullptr)
	{
		if (mapManager->IsCleared() || mapManager->Is(MapInfo::Wall, newPos))
		{
			return;
		}

		Engine::Ptr<Package> package;
		if (mapManager->GetPackagePos(newPos, &package))
		{
			if (!package->CanMove(input))
			{
				return;
			}

			package->Push(input);
			bPush = true;
		}
	}

	SetPosition(newPos);
	prevInputs.push({ input, bPush });
}

void Player::undo()
{
	if (mapManager != nullptr && !mapManager->IsCleared() && prevInputs.size() > 0)
	{
		Record record = prevInputs.top();
		prevInputs.pop();

		Int2 reversedInput = record.input * -1;

		if (record.bPush)
		{
			Int2 packagePos = GetPosition() + record.input;
			Engine::Ptr<Package> package;
			if (mapManager->GetPackagePos(packagePos, &package))
			{
				package->Push(reversedInput);
			}
		}

		Int2 newPos = GetPosition() + reversedInput;
		SetPosition(newPos);
	}
}
