#pragma once

#include "Ptr.h"

#include "Engine/Object/Object.h"

template <typename T>
Elysia::Engine::Ptr<T>::Ptr()
	: ptr(nullptr)
{
}

template <typename T>
Elysia::Engine::Ptr<T>::Ptr(T* _ptr)
	: ptr(_ptr)
{
	Object::AddIPtr(ptr, this);
}

template <typename T>
Elysia::Engine::Ptr<T>::Ptr(T& _ptr)
	: ptr(&_ptr)
{
	Object::AddIPtr(ptr, this);
}

template <typename T>
Elysia::Engine::Ptr<T>::Ptr(const Ptr& source)
	: ptr(source.ptr)
{
	Object::AddIPtr(ptr, this);
}

template <typename T>
Elysia::Engine::Ptr<T>::~Ptr()
{
	Object::DeleteIPtr(ptr, this);
}

template <typename T>
auto Elysia::Engine::Ptr<T>::operator=(const Ptr& source) -> Ptr&
{
	if (this != &source)
	{
		if (ptr != nullptr)
		{
			Object::DeleteIPtr(ptr, this);
		}

		ptr = source.ptr;
		Object::AddIPtr(ptr, this);
	}

	return *this;
}

template <typename T>
auto Elysia::Engine::Ptr<T>::operator=(T* _ptr) -> Ptr&
{
	if (ptr != nullptr)
	{
		Object::DeleteIPtr(ptr, this);
	}

	ptr = _ptr;
	Object::AddIPtr(ptr, this);

	return *this;
}

template <typename T>
auto Elysia::Engine::Ptr<T>::operator=(T& _ptr) -> Ptr&
{
	if (ptr != nullptr)
	{
		Object::DeleteIPtr(ptr, this);
	}

	ptr = &_ptr;
	Object::AddIPtr(ptr, this);

	return *this;
}

template <typename T>
T* Elysia::Engine::Ptr<T>::operator->()
{
	assert(ptr != nullptr);

	return ptr;
}

template <typename T>
const T* Elysia::Engine::Ptr<T>::operator->() const
{
	assert(ptr != nullptr);

	return ptr;
}

template <typename T>
bool Elysia::Engine::Ptr<T>::operator==(T* _ptr) const
{
	return ptr == _ptr;
}

template <typename T>
bool Elysia::Engine::Ptr<T>::operator!=(T* _ptr) const
{
	return !operator==(_ptr);
}

template <typename T>
Elysia::Engine::Ptr<T>::operator bool() const
{
	return ptr != nullptr;
}

template <typename T>
void Elysia::Engine::Ptr<T>::Invalidate()
{
	ptr = nullptr;
}
