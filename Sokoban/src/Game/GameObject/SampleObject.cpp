#include "SampleObject.h"

#include "Engine/GameFramework/GameFramework.h"
#include "Engine/GameFramework/InputManager.h"
#include "Engine/Component/ImageComponent.h"
#include "resource.h"

using Elysia::Game::SampleObject;

SampleObject::SampleObject(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene)
	: GameObject(_name, _instanceID, _scene)
{
	imageComponent = &AddComponent<Engine::ImageComponent>(TEXT("image"));
	imageComponent->SetPosition({ 100, 100 });
	imageComponent->SetImage(IDB_SAMPLE2);

	Engine::GameFramework::GetInstance().GetInputManager().RegisterKey(this, VK_UP, &SampleObject::moveUp);
	Engine::GameFramework::GetInstance().GetInputManager().RegisterKey(this, VK_DOWN, &SampleObject::moveDown);
}

SampleObject::~SampleObject()
{
}

void SampleObject::moveUp()
{
	Int2 pos = imageComponent->GetPosition();
	pos.y -= 10;

	imageComponent->SetPosition(pos);
}

void SampleObject::moveDown()
{
	Int2 pos = imageComponent->GetPosition();
	pos.y += 10;

	imageComponent->SetPosition(pos);
}
