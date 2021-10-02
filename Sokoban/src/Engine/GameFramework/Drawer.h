#pragma once

#include <Windows.h>
#include <unordered_map>

#include "Engine/EngineCommon.h"

namespace Elysia::Engine
{
class Drawer
{
	DELETE_COPY(Drawer);

	DELETE_MOVE(Drawer);

public:
	Drawer();

	~Drawer();

	void Load(int id);

	void LoadAll(std::initializer_list<int> idxes);

	void UnloadAll();

	void BeginPaint();

	void DrawBitmap(const Transform& transform, int bitmapID) const;

	void EndPaint();

private:
	std::unordered_map<int, HBITMAP> loadedBitmaps;

	PAINTSTRUCT ps;

	HDC hdc;
};
} // namespace Elysia::Engine
