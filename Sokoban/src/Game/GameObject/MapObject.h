#pragma once

#include "Engine/Object/GameObject.h"
#include "Engine/Object/Ptr.h"

namespace Elysia::Engine
{
class ImageComponent;
}

namespace Elysia::Game
{
class MapObject : public Engine::GameObject
{
	DECLARE_TYPENAME(MapObject);

public:
	MapObject(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene);

	virtual ~MapObject() override;

	void SetPosition(Int2 newPos);

	Int2 GetPosition() const;

protected:
	Engine::Ptr<Engine::ImageComponent> image;

private:
	Int2 pos;
};
} // namespace Elysia::Game
