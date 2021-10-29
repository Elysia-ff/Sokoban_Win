#include "Pointer.h"

#include "Engine/GameFramework/GameFramework.h"
#include "Engine/GameFramework/InputManager.h"
#include "Engine/Component/ImageComponent.h"

#include "Game/GameCommon.h"
#include "Game/GameObject/MapBuilder.h"

#include "resource.h"

using Elysia::Game::Pointer;

Pointer::Pointer(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene)
	: GameObject(_name, _instanceID, _scene)
	, isPressed(false)
	, posInUnit(0, 0)
{
	mapBuilder = FindGameObject<MapBuilder>(TEXT("MapBuilder"));

	image = AddComponent<Engine::ImageComponent>(TEXT("Image"));

	Engine::GameFramework& gameFramework = Engine::GameFramework::GetInstance();
	Engine::InputManager& inputManager = gameFramework.GetInputManager();
	inputManager.RegisterMouse(this, WM_MOUSEMOVE, &Pointer::onMouseMove);
	inputManager.RegisterMouse(this, WM_LBUTTONDOWN, &Pointer::onMouseDown);
	inputManager.RegisterMouse(this, WM_LBUTTONUP, &Pointer::onMouseUp);

	inputManager.RegisterCommand(this, ID_DRAWMODE_WALL, &Pointer::drawWall);
	inputManager.RegisterCommand(this, ID_DRAWMODE_GOAL, &Pointer::drawGoal);
	inputManager.RegisterCommand(this, ID_DRAWMODE_STARTSPOT, &Pointer::drawStartSpot);
	inputManager.RegisterCommand(this, ID_DRAWMODE_PACKAGE, &Pointer::drawPackage);
	inputManager.RegisterCommand(this, ID_DRAWMODE_ERASE, &Pointer::drawErase);

	drawWall();
}

Pointer::~Pointer()
{
}

Int2 Pointer::GetPosInUnit() const
{
	return posInUnit;
}

Int2 Pointer::GetPosition() const
{
	assert(image != nullptr);

	return image->GetPosition();
}

int Pointer::GetImage() const
{
	assert(image != nullptr);

	return image->GetImage();
}

void Pointer::SetImage(int id)
{
	assert(image != nullptr);

	image->SetImage(id);
}

void Pointer::onMouseMove(Int2 mousePosition)
{
	moveTo(mousePosition);

	if (isPressed)
	{
		assert(image != nullptr);

		if (image->GetImage() == IDB_ERASE)
		{
			mapBuilder->DeleteItem(*this);
		}
		else
		{
			mapBuilder->AddItem(*this);
		}
	}
}

void Pointer::onMouseDown(Int2 mousePosition)
{
	isPressed = true;
}

void Pointer::onMouseUp(Int2 mousePosition)
{
	assert(image != nullptr);

	if (image->GetImage() == IDB_ERASE)
	{
		mapBuilder->DeleteItem(*this);
	}
	else
	{
		mapBuilder->AddItem(*this);
	}

	isPressed = false;
}

void Pointer::moveTo(Int2 mousePosition)
{
	posInUnit = mousePosition / UNIT_PIXEL;
	Int2 newPos = posInUnit * UNIT_PIXEL;

	image->SetPosition(newPos);
}

void Pointer::drawWall()
{
	if (image != nullptr)
	{
		image->SetImage(IDB_WALL);
	}
}

void Pointer::drawGoal()
{
	if (image != nullptr)
	{
		image->SetImage(IDB_GOAL_EMPTY);
	}
}

void Pointer::drawStartSpot()
{
	if (image != nullptr)
	{
		image->SetImage(IDB_MAN_FRONT);
	}
}

void Pointer::drawPackage()
{
	if (image != nullptr)
	{
		image->SetImage(IDB_PACKAGE);
	}
}

void Pointer::drawErase()
{
	if (image != nullptr)
	{
		image->SetImage(IDB_ERASE);
	}
}
