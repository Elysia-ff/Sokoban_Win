#include "Component.h"

using Elysia::Engine::Component;

Component::Component(const tstring& _name)
	: Object(_name)
{
}

Component::~Component()
{
}

void Component::OnPaint() const
{
}
