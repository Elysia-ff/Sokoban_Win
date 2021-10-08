#pragma once

#include <unordered_map>
#include <unordered_set>

#include "Engine/EngineCommon.h"

namespace Elysia::Engine
{
class IPtr;

class Object
{
	DECLARE_TYPENAME(Object);

	DELETE_COPY(Object);

	DELETE_MOVE(Object);

public:
	static void* operator new(size_t size);

	static void operator delete(void* ptr) noexcept;

	static void AddIPtr(void* p, IPtr* iptr);

	static void DeleteIPtr(void* p, IPtr* iptr);

private:
	static std::unordered_map<void*, std::unordered_set<IPtr*>> allocatedMems;

public:
	Object() = delete;

	Object(const tstring& _name);

	virtual ~Object();

	const tstring& GetName() const;

private:
	tstring name;
};
} // namespace Elysia::Engine
