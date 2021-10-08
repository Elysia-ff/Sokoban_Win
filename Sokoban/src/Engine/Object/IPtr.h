#pragma once

namespace Elysia::Engine
{
class IPtr
{
public:
	virtual void Invalidate() = 0;
};
} // Elysia::Engine
