#pragma once

#include <unordered_map>

#include "Engine/Object/GameObject.h"
#include "Engine/Object/Ptr.h"

namespace Elysia::Engine
{
class ImageComponent;
}

namespace Elysia::Game
{
class Pointer;

class MapBuilder : public Engine::GameObject
{
	DECLARE_TYPENAME(MapBuilder);

public:
	MapBuilder(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene);

	virtual ~MapBuilder() override;

	void AddItem(const Pointer& pointer);

private:
	std::unordered_map<Int2, Engine::Ptr<Engine::ImageComponent>> items;
};
} // namespace Elysia::Game
