#include "SampleObject.h"

#include "Engine/Component/ImageComponent.h"
#include "resource.h"

using Elysia::Game::SampleObject;

SampleObject::SampleObject(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene)
	: GameObject(_name, _instanceID, _scene)
{
	Engine::ImageComponent& component = AddComponent<Engine::ImageComponent>(TEXT("image"));
	component.SetPosition({ 100, 100 });
	component.SetImage(IDB_SAMPLE2);
}

SampleObject::~SampleObject()
{
}
