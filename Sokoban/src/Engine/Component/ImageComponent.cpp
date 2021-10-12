#include "ImageComponent.h"

#include "Engine/GameFramework/GameFramework.h"
#include "Engine/GameFramework/Drawer.h"

using Elysia::Engine::ImageComponent;

ImageComponent::ImageComponent(const tstring& _name)
	: TransformComponent(_name)
	, imageID(-1)
{
}

ImageComponent::~ImageComponent()
{
}

void ImageComponent::OnPaint() const
{
	TransformComponent::OnPaint();

	if (IsActive())
	{
		GameFramework::GetInstance().GetDrawer().DrawBitmap(GetTransform(), imageID);
	}
}

void ImageComponent::SetImage(int newImageID)
{
	imageID = newImageID;
}

int ImageComponent::GetImage() const
{
	return imageID;
}
