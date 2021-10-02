#pragma once

#include "Engine/EngineCommon.h"

namespace Elysia::Engine
{
class Object
{
	DECLARE_TYPENAME(Object);

	DELETE_COPY(Object);

	DELETE_MOVE(Object);

public:
	Object() = delete;

	Object(const tstring& _name);

	virtual ~Object();

	const tstring& GetName() const;

private:
	tstring name;
};
} // namespace Elysia::Engine
