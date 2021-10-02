#pragma once

#include "Engine/Component/Component.h"

namespace Elysia::Engine
{
class TransformComponent : public Component
{
	DECLARE_TYPENAME(TransformComponent);

public:
	TransformComponent(const tstring& _name);

	virtual ~TransformComponent() override;

	virtual void OnPaint() const override;

	const Transform& GetTransform() const;

	void SetPosition(Int2 newPos);

	Int2 GetPosition() const;

	void SetScale(Int2 newScale);

	Int2 GetScale() const;

private:
	Transform transform;
};
}; // namespace Elysia::Engine
