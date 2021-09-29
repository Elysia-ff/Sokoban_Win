#include "MainWindow.h"

using Elysia::Window::MainWindow;

MainWindow::MainWindow(LPCTSTR className, HINSTANCE hInstance)
	: WindowBase(className, hInstance)
{
}

MainWindow::~MainWindow()
{
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
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
