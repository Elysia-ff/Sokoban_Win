#pragma once

#include "Engine/Object/GameObject.h"
#include "Engine/Object/Ptr.h"

namespace Elysia::Engine
{
class ImageComponent;
}

namespace Elysia::Game
{
class MapBuilder;

class Pointer : public Engine::GameObject
{
	DECLARE_TYPENAME(Pointer);

public:
	Pointer(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene);

	virtual ~Pointer() override;

	Int2 GetPosInUnit() const;

	Int2 GetPosition() const;

	int GetImage() const;

	void SetImage(int id);

private:
	void onMouseMove(Int2 mousePosition);

	void onMouseDown(Int2 mousePosition);

	void onMouseUp(Int2 mousePosition);

	void moveTo(Int2 mousePosition);

private:
	Engine::Ptr<MapBuilder> mapBuilder;

	Engine::Ptr<Engine::ImageComponent> image;

	bool isPressed;

	Int2 posInUnit;
};
} // namespace Elysia::Game
