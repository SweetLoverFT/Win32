#include "stdafx.h"
#include "MainWindow.h"

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int)
{
    MainWindow win;
    if (!win.Create(L"Circle", WS_OVERLAPPEDWINDOW))
        return EXIT_FAILURE;

	::ShowWindow(win.Window(), SW_NORMAL);
	::UpdateWindow(win.Window());

    // Use accelerator to handle WM_COMMAND generated from keyboard shortcuts, menu and toolbar
    // Please refer to https://docs.microsoft.com/zh-cn/windows/win32/learnwin32/accelerator-tables
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCEL));

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // Handle WM_COMMAND at the 1st priority and other Windows messages at the 2nd priority
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            ::TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return static_cast<int>(msg.wParam);
}
