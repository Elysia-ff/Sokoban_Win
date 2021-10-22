#include "MainWindow.h"

#include "Engine/GameFramework/GameFramework.h"

#include "resource.h"

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
	wndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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
	case WM_KEYDOWN:
	{
		onKeyDown(wParam);

		return 0;
	}
	case WM_COMMAND:
	{
		onCommand(wParam);

		return 0;
	}
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	{
		onMouse(uMsg, lParam);
		
		return 0;
	}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void MainWindow::onCreate()
{
	Engine::GameFramework::Allocate(*this);

	Engine::GameFramework::GetInstance().LoadSceneByIdx(0);
}

void MainWindow::onDestroy()
{
	Engine::GameFramework::Release();
}

void MainWindow::onPaint() const
{
	Engine::GameFramework::GetInstance().OnPaint();
}

void MainWindow::onKeyDown(WPARAM key) const
{
	Engine::GameFramework::GetInstance().OnKeyDown(key);
}

void MainWindow::onCommand(WPARAM wParam) const
{
	Engine::GameFramework::GetInstance().OnCommand(wParam);
}

void MainWindow::onMouse(UINT msg, LPARAM lParam) const
{
	Engine::GameFramework::GetInstance().OnMouse(msg, lParam);
}
