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
	image->SetImage(IDB_WALL);

	Engine::GameFramework& gameFramework = Engine::GameFramework::GetInstance();
	Engine::InputManager& inputManager = gameFramework.GetInputManager();
	inputManager.RegisterMouse(this, WM_MOUSEMOVE, &Pointer::onMouseMove);
	inputManager.RegisterMouse(this, WM_LBUTTONDOWN, &Pointer::onMouseDown);
	inputManager.RegisterMouse(this, WM_LBUTTONUP, &Pointer::onMouseUp);
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
		mapBuilder->AddItem(*this);
	}
}

void Pointer::onMouseDown(Int2 mousePosition)
{
	isPressed = true;
}

void Pointer::onMouseUp(Int2 mousePosition)
{
	mapBuilder->AddItem(*this);

	isPressed = false;
}

void Pointer::moveTo(Int2 mousePosition)
{
	posInUnit = mousePosition / UNIT_PIXEL;
	Int2 newPos = posInUnit * UNIT_PIXEL;

	image->SetPosition(newPos);
}
