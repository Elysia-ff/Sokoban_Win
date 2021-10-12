#include "Component.h"

using Elysia::Engine::Component;

Component::Component(const tstring& _name)
	: Object(_name)
	, isActive(true)
{
}

Component::~Component()
{
}

void Component::OnPaint() const
{
}

void Component::SetActive(bool value)
{
	isActive = value;
}

bool Component::IsActive() const
{
	return isActive;
}
