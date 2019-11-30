#pragma once

#include "BaseWindow.h"
#include <d2d1.h>

class MainWindow
    : public BaseWindow<MainWindow>
{
private:
    void    CalculateLayout();
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    OnResize();
    void    OnLButtonDown(int pixelX, int pixelY, DWORD flags);
    void    OnLButtonUp();
    void    OnMouseMove(int pixelX, int pixelY, DWORD flags);
public:
    MainWindow()
        : BaseWindow<MainWindow>()
        , m_pFactory(nullptr)
        , m_pRenderTarget(nullptr)
        , m_pBrush(nullptr)
        , m_ellipse(D2D1::Ellipse(D2D1::Point2F(), 0, 0))
        , m_ptMouse(D2D1::Point2F())
    {

    }
    virtual ~MainWindow() { }
public:
    virtual PCWSTR  ClassName() const override { return L"Sample Window Class"; }
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
private:
    ID2D1Factory            *m_pFactory;
    ID2D1HwndRenderTarget   *m_pRenderTarget;
    ID2D1SolidColorBrush    *m_pBrush;
    D2D1_ELLIPSE            m_ellipse;
    D2D1_POINT_2F           m_ptMouse;
};
