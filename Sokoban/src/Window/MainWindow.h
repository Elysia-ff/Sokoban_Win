#pragma once

#include "WindowBase.h"

namespace Elysia::Engine
{
class Drawer;
}

namespace Elysia::Window
{
class MainWindow : public WindowBase<MainWindow>
{
	friend WindowBase<MainWindow>;

protected:
	MainWindow(LPCTSTR className, HINSTANCE hInstance);

	virtual ~MainWindow() override;

	virtual WNDCLASS GetWndClass() const override;

	virtual WNDOPTION GetWndOption() const override;

	virtual LRESULT CALLBACK HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

private:
	Engine::Drawer* drawer;
};
} // namespace Elysia::Window
