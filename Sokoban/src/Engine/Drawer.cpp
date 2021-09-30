#include "Drawer.h"

#include <cassert>

using Elysia::Engine::Drawer;

Drawer::Drawer()
{
}

Drawer::Drawer(Drawer&& source) noexcept
	: loadedBitmaps(std::move(source.loadedBitmaps))
{
}

Drawer::~Drawer()
{
	UnloadAll();
}

Drawer& Drawer::operator=(Drawer&& source) noexcept
{
	if (this != &source)
	{
		loadedBitmaps = std::move(source.loadedBitmaps);
	}

	return *this;
}

void Drawer::Load(HINSTANCE hInstance, int id)
{
	assert(loadedBitmaps.find(id) == loadedBitmaps.end());

	HBITMAP handle = static_cast<HBITMAP>(LoadImage(hInstance, MAKEINTRESOURCE(id), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR));
	assert(handle != nullptr);

	loadedBitmaps.insert({ id, handle });
}

void Drawer::LoadAll(HINSTANCE hInstance, const std::initializer_list<int>& idxes)
{
	for (int id : idxes)
	{
		Load(hInstance, id);
	}
}

void Drawer::UnloadAll()
{
	for (auto& kv : loadedBitmaps)
	{
		DeleteObject(kv.second);
	}

	loadedBitmaps.clear();
}

void Drawer::DrawBitmap(HDC hdc, Int2 pos, int bitmapID) const
{
	assert(loadedBitmaps.find(bitmapID) != loadedBitmaps.end());
	auto iter = loadedBitmaps.find(bitmapID);

	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP bitmap = iter->second;
	HBITMAP oldBitmap = static_cast<HBITMAP>(SelectObject(memDC, bitmap));

	BITMAP temp{};
	GetObject(bitmap, sizeof(BITMAP), &temp);
	BitBlt(hdc, pos.x, pos.y, temp.bmWidth, temp.bmHeight, memDC, 0, 0, SRCCOPY);

	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);
}
