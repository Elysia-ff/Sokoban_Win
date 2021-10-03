#include "Drawer.h"

#include <cassert>

#include "Engine/GameFramework/GameFramework.h"
#include "Window/MainWindow.h"

using Elysia::Engine::Drawer;

Drawer::Drawer()
	: loadedBitmaps()
	, ps()
	, hdc()
{
}

Drawer::~Drawer()
{
}

void Drawer::Load(int id)
{
	assert(loadedBitmaps.find(id) == loadedBitmaps.end());

	HINSTANCE hInstance = GameFramework::GetInstance().GetWindow().GetHInstance();
	HBITMAP handle = static_cast<HBITMAP>(LoadImage(hInstance, MAKEINTRESOURCE(id), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR));
	assert(handle != nullptr);

	loadedBitmaps.insert({ id, handle });
}

void Drawer::LoadAll(std::initializer_list<int> idxes)
{
	for (int id : idxes)
	{
		Load(id);
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

void Drawer::BeginPaint()
{
	HWND hWnd = GameFramework::GetInstance().GetWindow().GetHandle();
	hdc = ::BeginPaint(hWnd, &ps);
}

void Drawer::DrawBitmap(const Transform& transform, int bitmapID) const
{
	assert(loadedBitmaps.find(bitmapID) != loadedBitmaps.end());
	auto iter = loadedBitmaps.find(bitmapID);

	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP bitmap = iter->second;
	HBITMAP oldBitmap = static_cast<HBITMAP>(SelectObject(memDC, bitmap));

	BITMAP temp{};
	GetObject(bitmap, sizeof(BITMAP), &temp);

	int x = transform.position.x;
	int y = transform.position.y;
	int width = static_cast<int>(temp.bmWidth) * transform.scale.x;
	int height = static_cast<int>(temp.bmHeight) * transform.scale.y;
	StretchBlt(hdc, x, y, width, height, memDC, 0, 0, temp.bmWidth, temp.bmHeight, SRCCOPY);

	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);
}

void Drawer::EndPaint()
{
	HWND hWnd = GameFramework::GetInstance().GetWindow().GetHandle();
	::EndPaint(hWnd, &ps);
}
