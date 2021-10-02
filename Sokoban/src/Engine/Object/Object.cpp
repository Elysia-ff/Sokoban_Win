#include "Object.h"

using Elysia::Engine::Object;

Object::Object(const tstring& _name)
	: name(_name)
{
}

Object::~Object()
{
}

const tstring& Object::GetName() const
{
	return name;
}
