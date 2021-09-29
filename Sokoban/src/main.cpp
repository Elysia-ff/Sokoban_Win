#include <Windows.h>

#include "Window/MainWindow.h"

using Elysia::Window::MainWindow;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR pCmdLine, _In_ int nCmdShow)
{
	MainWindow* window = MainWindow::Create(TEXT("Sokoban"), hInstance);
	if (window->Show(TEXT("Sokoban"), nCmdShow) != 0)
	{
		MessageBox(nullptr, TEXT("Window creation failed!"), TEXT("Error"), MB_OK);

		return -1;
	}

	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	MainWindow::Release();

	return static_cast<int>(msg.wParam);
}
