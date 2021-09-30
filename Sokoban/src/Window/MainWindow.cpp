#include "MainWindow.h"

#include "Engine/Drawer.h"
#include "resource.h"

using Elysia::Window::MainWindow;
using Elysia::Engine::Drawer;

MainWindow::MainWindow(LPCTSTR className, HINSTANCE hInstance)
	: WindowBase(className, hInstance)
	, drawer(new Drawer())
{
	drawer->LoadAll(hInstance, { IDB_SAMPLE1, IDB_SAMPLE2 });
}

MainWindow::~MainWindow()
{
	delete drawer;
}

WNDCLASS MainWindow::GetWndClass() const
{
	WNDCLASS wndClass{};
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(COLOR_WINDOW + 1));
	wndClass.style = CS_VREDRAW | CS_HREDRAW;

	return wndClass;
}

auto MainWindow::GetWndOption() const -> WNDOPTION
{
	WNDOPTION wndOption{};
	wndOption.dwStyle = WS_OVERLAPPEDWINDOW;
	wndOption.x = CW_USEDEFAULT;
	wndOption.y = CW_USEDEFAULT;
	wndOption.nWidth = CW_USEDEFAULT;
	wndOption.nHeight = CW_USEDEFAULT;

	return wndOption;
}

LRESULT CALLBACK MainWindow::HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);

		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(GetHandle(), &ps);

		drawer->DrawBitmap(hdc, { 0, 0 }, IDB_SAMPLE1);
		drawer->DrawBitmap(hdc, { 100, 100 }, IDB_SAMPLE2);

		EndPaint(GetHandle(), &ps);

		return 0;
	}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
