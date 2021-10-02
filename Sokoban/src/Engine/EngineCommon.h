#pragma once

#include <Windows.h>
#include <string>

#include "Engine/Transform.h"

using tstring = std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>>;

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
