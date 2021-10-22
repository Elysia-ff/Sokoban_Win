#pragma once

#include "Window/WindowBase.h"

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
	void onCreate();

	void onDestroy();

	void onPaint() const;

	void onKeyDown(WPARAM key) const;

	void onCommand(WPARAM wParam) const;

	void onMouse(UINT msg, LPARAM lParam) const;
};
} // namespace Elysia::Window
