#include "Object.h"

#include <cassert>
#include "Engine/Object/IPtr.h"

using Elysia::Engine::Object;

std::unordered_map<void*, std::unordered_set<Elysia::Engine::IPtr*>> Object::allocatedMems;

void* Object::operator new(size_t size)
{
	void* ptr = malloc(size);

	assert(allocatedMems.find(ptr) == allocatedMems.end());
	allocatedMems.insert({ ptr, std::unordered_set<Elysia::Engine::IPtr*>() });

	return ptr;
}

void Object::operator delete(void* ptr)
{
	auto iter = allocatedMems.find(ptr);
	assert(iter != allocatedMems.end());
	
	for (Elysia::Engine::IPtr* p : iter->second)
	{
		p->Invalidate();
	}
	allocatedMems.erase(iter);

	free(ptr);
}

void Object::AddIPtr(void* p, Elysia::Engine::IPtr* iptr)
{
	if (p != nullptr)
	{
		assert(iptr != nullptr);
		assert(allocatedMems.find(p) != allocatedMems.end());

		allocatedMems[p].insert(iptr);
	}
}

void Object::DeleteIPtr(void* p, Elysia::Engine::IPtr* iptr)
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
