#pragma once

namespace Elysia::Game
{
enum class MapInfo : char
{
	None	= ' ',
	Wall	= 'x',
	Start	= 'p',
	Pack	= 'o',
	Goal	= '#',
};

constexpr int UNIT_PIXEL = 32;
} // namespace Elysia::Game
