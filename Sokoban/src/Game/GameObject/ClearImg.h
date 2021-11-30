#pragma once

#include "Engine/Object/Ptr.h"
#include "Engine/Object/GameObject.h"

namespace Elysia::Engine
{
class ImageComponent;
}

namespace Elysia::Game
{
class ClearImg : public Engine::GameObject
{
	DECLARE_TYPENAME(ClearImg);

public:
	ClearImg(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene);

	virtual ~ClearImg() override;

	void MoveToCenter(int mapWidth, int mapHeight);

private:
	Engine::Ptr<Engine::ImageComponent> image;
};
} // namespace Elysia::Game
