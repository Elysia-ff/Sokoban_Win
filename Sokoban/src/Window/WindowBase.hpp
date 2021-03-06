#pragma once

#include "WindowBase.h"

#include <cassert>
#include <utility>

template <typename T>
template <typename... Args>
T* Elysia::Window::WindowBase<T>::Create(LPCTSTR className, HINSTANCE hInstance, Args&&... args)
{
	assert(Window == nullptr);
	Window = new T(className, hInstance, std::forward<Args>(args)...);

	return Window;
}

template <typename T>
void Elysia::Window::WindowBase<T>::Release()
{
	delete Window;

	Window = nullptr;
}

template <typename T>
bool Elysia::Window::WindowBase<T>::IsActive()
{
	return Window != nullptr && IsWindow(Window->GetHandle());
}

template <typename T>
LRESULT CALLBACK Elysia::Window::WindowBase<T>::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	assert(Window != nullptr);

	return Window->HandleMessage(hWnd, uMsg, wParam, lParam);
}

template <typename T>
HINSTANCE Elysia::Window::WindowBase<T>::GetHInstance() const
{
	return m_hInstance;
}

template <typename T>
HWND Elysia::Window::WindowBase<T>::GetHandle() const
{
	return m_hWnd;
}

template <typename T>
int Elysia::Window::WindowBase<T>::Show(LPCTSTR title, int nCmdShow)
{
	WNDCLASS wndClass = GetWndClass();
	wndClass.lpfnWndProc = &T::WndProc;
	wndClass.hInstance = GetHInstance();
	wndClass.lpszClassName = m_className;
	RegisterClass(&wndClass);

	WNDOPTION wndOption = GetWndOption();
	m_hWnd = CreateWindowEx(
		wndOption.dwExStyle,
		m_className,
		title,
		wndOption.dwStyle,
		wndOption.x, wndOption.y, wndOption.nWidth, wndOption.nHeight,
		wndOption.hWndParent,
		wndOption.hMenu,
		GetHInstance(),
		wndOption.lpParam
	);

	if (m_hWnd == nullptr)
	{
		return -1;
	}

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return 0;
}

template <typename T>
Elysia::Window::WindowBase<T>::WindowBase(LPCTSTR className, HINSTANCE hInstance)
	: m_className(className)
	, m_hInstance(hInstance)
	, m_hWnd(nullptr)
{
}

template <typename T>
Elysia::Window::WindowBase<T>::~WindowBase()
{
}

template <typename T>
WNDCLASS Elysia::Window::WindowBase<T>::GetWndClass() const
{
	WNDCLASS wndClass{};
	wndClass.lpfnWndProc = &T::WndProc;
	wndClass.hInstance = GetHInstance();
	wndClass.lpszClassName = m_className;

	return wndClass;
}
