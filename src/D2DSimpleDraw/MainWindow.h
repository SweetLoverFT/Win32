#pragma once

#include "Ellipse.h"
#include "BaseWindow.h"

class MainWindow
    : public BaseWindow<MainWindow>
{
private:
    void    CalculateLayout();
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
private:
    HRESULT SetMode(WORD wCmd);
    /*!
     *  \brief Confine the cursor
     *  \note Please refer to https://docs.microsoft.com/zh-cn/windows/win32/learnwin32/other-mouse-operations
     */
    HRESULT ConfineCursor();
private:
    void    OnCreate();
    void    OnDestroy();
    void    OnPaint();
    void    OnResize();
    /*!
     *  \brief Handle mouse movement
     *  \note Please refer to https://docs.microsoft.com/zh-cn/windows/win32/learnwin32/mouse-movement
     */
    void    OnMouseMove(int pixelX, int pixelY, DWORD flags);
    void    OnLButtonDown(int pixelX, int pixelY, DWORD flags);
    void    OnLButtonUp(int pixelX, int pixelY, DWORD flags);
public:
    MainWindow()
        : BaseWindow<MainWindow>()
        , m_pFactory(nullptr)
        , m_pRenderTarget(nullptr)
        , m_pBrush(nullptr)
        , m_ellipse(D2D1::Ellipse(D2D1::Point2F(), 0, 0))
        , m_ptMouse(D2D1::Point2F())
        , m_hCursor(LoadCursor(nullptr, IDC_ARROW))
        , m_wMode(ID_SELECT_MODE)
        , m_pEllipse(nullptr)
        , m_bIsConfineCursor(false)
    {
        
    }
    virtual ~MainWindow() { }
public:
    virtual PCTSTR  ClassName() const override { return _T("Sample Window Class"); }
    /*!
     *  \brief Handle user-defined commands, some of them are keyboard and mouse actions
     *  \note Please refer to https://docs.microsoft.com/zh-cn/windows/win32/learnwin32/mouse-clicks
     */
    LRESULT HandleCommand(WPARAM wParam, LPARAM lParam);
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
private:
    ID2D1Factory            *m_pFactory;
    ID2D1HwndRenderTarget   *m_pRenderTarget;
    ID2D1SolidColorBrush    *m_pBrush;
    D2D1_ELLIPSE            m_ellipse;
    D2D1_POINT_2F           m_ptMouse;
    HCURSOR                 m_hCursor;
    WORD                    m_wMode;
    struct Ellipse          *m_pEllipse;
    EllipseList             m_list;
    bool                    m_bIsConfineCursor;
};
