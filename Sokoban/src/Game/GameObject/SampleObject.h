#pragma once

#include "Engine/Object/GameObject.h"
#include "Engine/Object/Ptr.h"

namespace Elysia::Engine
{
class ImageComponent;
}

namespace Elysia::Game
{
class SampleObject : public Engine::GameObject
{
	DECLARE_TYPENAME(SampleObject);

public:
	SampleObject(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene);

	virtual ~SampleObject() override;

private:
	void moveUp();

	void moveDown();

	void remove();

private:
	Engine::Ptr<Engine::ImageComponent> imageComponent;
};
} // namespace Elysia::Game
