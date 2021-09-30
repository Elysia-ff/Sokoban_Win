#pragma once

#include <Windows.h>
#include <unordered_map>

#include "Engine/Int2.h"

namespace Elysia::Engine
{
class Drawer
{
public:
	Drawer();

	Drawer(const Drawer& source) = delete;

	Drawer(Drawer&& source) noexcept;

	~Drawer();

	Drawer& operator=(const Drawer& source) = delete;

	Drawer& operator=(Drawer&& source) noexcept;

	void Load(HINSTANCE hInstance, int id);

	void LoadAll(HINSTANCE hInstance, const std::initializer_list<int>& idxes);

	void UnloadAll();

	void DrawBitmap(HDC hdc, Int2 pos, int bitmapID) const;

private:
	std::unordered_map<int, HBITMAP> loadedBitmaps;
};
} // namespace Elysia::Engine
