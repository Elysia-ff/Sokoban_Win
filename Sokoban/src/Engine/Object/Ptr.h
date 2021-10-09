#pragma once

#include "Engine/EngineCommon.h"
#include "IPtr.h"

namespace Elysia::Engine
{
template <typename T>
class Ptr : public IPtr
{
public:
	Ptr();

	Ptr(T* _ptr);

	Ptr(T& _ptr);

	Ptr(const Ptr& source);

	~Ptr();

	Ptr& operator=(const Ptr& source);

	Ptr& operator=(T* _ptr);

	Ptr& operator=(T& _ptr);

	bool operator==(T* _ptr) const;

	bool operator!=(T* _ptr) const;

	operator bool() const;

	T* operator->();

	const T* operator->() const;

	virtual void Invalidate() override;

private:
	T* ptr;
};
} // namespace Elysia::Engine

#include "Ptr_Templates.hpp"
