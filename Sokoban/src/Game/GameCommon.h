#pragma once

#include <unordered_map>
#include <vector>

#include "resource.h"

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

inline static std::unordered_map<int, MapInfo> imageToMapInfo
{
	{ IDB_WALL, MapInfo::Wall },
	{ IDB_MAN_FRONT, MapInfo::Start },
	{ IDB_PACKAGE, MapInfo::Pack },
	{ IDB_GOAL_EMPTY, MapInfo::Goal }
};

constexpr int UNIT_PIXEL = 32;

using MapData = std::vector<std::vector<char>>;

using ReachedMapData = std::vector<std::vector<bool>>;
} // namespace Elysia::Game
