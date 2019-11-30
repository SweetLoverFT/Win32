#include "stdafx.h"
#include "MainWindow.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    MainWindow win;
    if (!win.Create(win.ClassName(), WS_OVERLAPPEDWINDOW))
        return 0;

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
