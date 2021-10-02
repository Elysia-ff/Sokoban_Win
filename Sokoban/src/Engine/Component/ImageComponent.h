#pragma once

#include "Engine/Component/TransformComponent.h"

namespace Elysia::Engine
{
class ImageComponent : public TransformComponent
{
	DECLARE_TYPENAME(ImageComponent);

public:
	ImageComponent(const tstring& _name);

	virtual ~ImageComponent() override;

	virtual void OnPaint() const override;

	void SetImage(int newImageID);

	int GetImage() const;

private:
	int imageID;
};
} // namespace Elysia::Engine
