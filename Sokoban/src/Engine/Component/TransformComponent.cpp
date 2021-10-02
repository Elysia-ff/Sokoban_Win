#include "TransformComponent.h"

using Elysia::Engine::TransformComponent;

TransformComponent::TransformComponent(const tstring& _name)
	: Component(_name)
	, transform{ {0, 0}, {1, 1} }
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::OnPaint() const
{
	Component::OnPaint();
}

const Transform& TransformComponent::GetTransform() const
{
	return transform;
}

void TransformComponent::SetPosition(Int2 newPos)
{
	transform.position = newPos;
}

Int2 TransformComponent::GetPosition() const
{
	return transform.position;
}

void TransformComponent::SetScale(Int2 newScale)
{
	transform.scale = newScale;
}

Int2 TransformComponent::GetScale() const
{
	return transform.scale;
}
