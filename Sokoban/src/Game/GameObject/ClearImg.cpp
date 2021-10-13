#include "ClearImg.h"

#include "Engine/GameFramework/GameFramework.h"
#include "Engine/GameFramework/InputManager.h"
#include "Engine/GameFramework/Drawer.h"
#include "Engine/Component/ImageComponent.h"

#include "Game/GameCommon.h"

#include "resource.h"

using Elysia::Game::ClearImg;

ClearImg::ClearImg(const tstring& _name, unsigned int _instanceID, Engine::Scene& _scene)
	: GameObject(_name, _instanceID, _scene)
{
	image = AddComponent<Engine::ImageComponent>(TEXT("image"));
	image->SetImage(IDB_CLEAR);

	Engine::GameFramework::GetInstance().GetInputManager().RegisterKey(this, VK_SPACE, &ClearImg::loadNextScene);
}

ClearImg::~ClearImg()
{
}

void ClearImg::MoveToCenter(int mapWidth, int mapHeight)
{
	if (image != nullptr)
	{
		Int2 size(mapWidth * UNIT_PIXEL, mapHeight * UNIT_PIXEL);
		Int2 center = size / 2;
		Int2 imageSize = Engine::GameFramework::GetInstance().GetDrawer().GetBitmapSize(image->GetImage());

		Int2 pos = center - (imageSize / 2);
		image->SetPosition(pos);
	}
}

void ClearImg::loadNextScene()
{
	Engine::GameFramework& framework = Engine::GameFramework::GetInstance();
	int nextSceneIdx = framework.GetCurrentSceneIdx() + 1;
	int sceneCount = framework.GetSceneCount();

	if (nextSceneIdx < sceneCount)
	{
		framework.LoadSceneByIdx(nextSceneIdx);
	}
	else
	{
		framework.LoadSceneByIdx(0);
	}
}