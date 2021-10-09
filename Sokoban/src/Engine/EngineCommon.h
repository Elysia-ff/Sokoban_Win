#pragma once

#include <Windows.h>
#include <string>

#include "Engine/Transform.h"

#if UNICODE

using tstring = std::wstring;
#define to_tstring(n) (std::to_wstring(n))

#else

using tstring = std::string;
#define to_tstring(n) (std::to_string(n))

#endif

#define DECLARE_TYPENAME(typeName) \
public:\
	static const tstring& GetTypeName()\
	{\
		return _typeName;\
	}\
\
private:\
	inline static const tstring _typeName = TEXT(#typeName);

#define DELETE_COPY(Type) \
public:\
	Type(const Type& source) = delete;\
	Type& operator=(const Type& source) = delete;

#define DELETE_MOVE(Type) \
public:\
	Type(Type&& source) noexcept = delete;\
	Type& operator=(Type&& source) noexcept = delete;

template <typename T>
constexpr Int2 MakeInt2(T x, T y)
{
	return Int2(static_cast<int>(x), static_cast<int>(y));
}
