#pragma once

#include <Windows.h>

namespace Elysia::Window
{
template <typename T>
class WindowBase
{
protected:
	struct WNDOPTION
	{
		DWORD dwExStyle;
		DWORD dwStyle;
		int x;
		int y;
		int nWidth;
		int nHeight;
		HWND hWndParent;
		HMENU hMenu;
		LPVOID lpParam;
	};

public:
	template <typename... Args>
	static T* Create(LPCTSTR className, HINSTANCE hInstance, Args&&... args);

	static void Release();

	static bool IsActive();

protected:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	inline static T* Window = nullptr;

public:
	HINSTANCE GetHInstance() const;

	HWND GetHandle() const;

	int Show(LPCTSTR title, int nCmdShow);

protected:
	WindowBase() = delete;

	WindowBase(LPCTSTR className, HINSTANCE hInstance);

	virtual ~WindowBase();

	virtual WNDCLASS GetWndClass() const = 0;

	virtual WNDOPTION GetWndOption() const = 0;

	virtual LRESULT CALLBACK HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

private:
	LPCTSTR m_className;

	HINSTANCE m_hInstance;

	HWND m_hWnd;
};
} // namespace Elysia::Window

#include "WindowBase.hpp"
