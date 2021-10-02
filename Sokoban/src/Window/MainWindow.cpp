#include "MainWindow.h"

#include "Engine/GameFramework/GameFramework.h"

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
	case WM_CREATE:
	{
		onCreate();

		return 0;
	}
	case WM_DESTROY:
	{
		onDestroy();
		PostQuitMessage(0);

		return 0;
	}
	case WM_PAINT:
	{
		onPaint();

		return 0;
	}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void MainWindow::onCreate()
{
	Engine::GameFramework::Allocate(*this);

	Engine::GameFramework::GetInstance()->LoadSceneByIdx(0);
}

void MainWindow::onDestroy()
{
	Engine::GameFramework::Release();
}

void MainWindow::onPaint() const
{
	Engine::GameFramework::GetInstance()->OnPaint();
}
