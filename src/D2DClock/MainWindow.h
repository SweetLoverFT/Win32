#pragma once

#include "BaseWindow.h"
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

class MainWindow
    : public BaseWindow<MainWindow>
{
    /*!
     *  In Direct2D, we use DIPs (Device-independent pixels) instead of DPI (Dots per inch).
     *  Therefore, the units of measurement are consistent for both text and drawing,
     *  regardless of the current DPI setting.
     *  But for GDI, mouse and window coordinate are still given in physical pixels.
     *  Link: https://docs.microsoft.com/zh-cn/windows/desktop/LearnWin32/dpi-and-device-independent-pixels.
     */
private:
    static void InitializeDPIScale(ID2D1Factory *pFactory);
    static void InitializeDPIScale(HWND hwnd);
    static void PixelsToDips(int x, int y, double *pX, double * pY);
private:
    void    CalculateLayout();
    void    DrawClockHand(float fHandLength, float fAngle, float fStrokeWidth);
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    OnResize();
public:
    MainWindow()
        : BaseWindow<MainWindow>()
        , m_pFactory(nullptr)
        , m_pRenderTarget(nullptr)
        , m_pBrush(nullptr)
    {

    }
    virtual ~MainWindow() { }
public:
    virtual PCWSTR  ClassName() const override { return L"Sample Window Class"; }
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
private:
    static double           s_DPIScaleX;
    static double           s_DPIScaleY;
private:
    ID2D1Factory            *m_pFactory;
    ID2D1HwndRenderTarget   *m_pRenderTarget;
    ID2D1SolidColorBrush    *m_pBrush;
    ID2D1SolidColorBrush    *m_pBrushBlack;
    ID2D1StrokeStyle        *m_pStroke;
    D2D1_ELLIPSE            m_ellipse;
private:
    enum
    {
        ID_TIMER_UPDATE     = 1001,

        DELAY_TIME          = 1000,
    };
};
