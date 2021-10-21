#pragma once

#include "Engine/Object/GameObject.h"
#include "Engine/Object/Ptr.h"

namespace Elysia::Engine
{
class ImageComponent;
}

namespace Elysia::Game
{
class Pointer : public Engine::GameObject
{
	DECLARE_TYPENAME(Pointer);

public:
	Pointer(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene);

	virtual ~Pointer() override;

private:
	Engine::Ptr<Engine::ImageComponent> image;

	bool isPressed;
};
} // namespace Elysia::Game
