#include "stdafx.h"
#include "MainWindow.h"

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    MainWindow win;
    if (!win.Create(L"Circle", WS_OVERLAPPEDWINDOW))
        return EXIT_FAILURE;

    ::ShowWindow(win.Window(), nCmdShow);
	::UpdateWindow(win.Window());

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        ::TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}
