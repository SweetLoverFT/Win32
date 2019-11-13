#pragma once

#include "BaseWindow.h"

class MainWindow
    : public BaseWindow<MainWindow>
{
public:
    MainWindow() : BaseWindow<MainWindow>(m_hWnd) { };
    virtual ~MainWindow() { }
// Originally, the access control is protected. It's allowed to change the access control
public:
    virtual PCWSTR  ClassName() const override { return L"Sample Window Class"; }
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        ::PostQuitMessage(0);
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hWnd, &ps);
        ::FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>((COLOR_WINDOW + 1)));
        EndPaint(m_hWnd, &ps);
		break;
    }
    }
    return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}
