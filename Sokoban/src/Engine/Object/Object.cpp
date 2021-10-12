#include "Object.h"

#include <cassert>
#include "Engine/Object/IPtr.h"

using Elysia::Engine::Object;

std::unordered_map<Object*, std::unordered_set<Elysia::Engine::IPtr*>> Object::allocatedMems;

void* Object::operator new(size_t size)
{
	void* ptr = malloc(size);

	Object* oPtr = static_cast<Object*>(ptr);
	assert(allocatedMems.find(oPtr) == allocatedMems.end());
	allocatedMems.insert({ oPtr, std::unordered_set<Elysia::Engine::IPtr*>() });

	return ptr;
}

void Object::operator delete(void* ptr)
{
	Object* oPtr = static_cast<Object*>(ptr);
	auto iter = allocatedMems.find(oPtr);
	assert(iter != allocatedMems.end());
	
	for (Elysia::Engine::IPtr* p : iter->second)
	{
		p->Invalidate();
	}
	allocatedMems.erase(iter);

	free(ptr);
}

void Object::AddIPtr(Object* p, Elysia::Engine::IPtr* iptr)
{
	if (p != nullptr)
	{
		assert(iptr != nullptr);
		assert(allocatedMems.find(p) != allocatedMems.end());

		allocatedMems[p].insert(iptr);
	}
}

void Object::DeleteIPtr(Object* p, Elysia::Engine::IPtr* iptr)
{
	if (p != nullptr)
	{
		assert(iptr != nullptr);
		assert(allocatedMems.find(p) != allocatedMems.end());

		std::unordered_set<IPtr*>& list = allocatedMems[p];
		auto iter = list.find(iptr);
		if (iter != list.end())
		{
			list.erase(iter);
		}
	}
}

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
