#pragma once

#include "Ellipse.h"
#include "BaseWindow.h"
#include "MouseTrackEvents.h"

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

    void    OnFileOpen();
    void    OnFileSave();

    /*!
     *  \brief Handle mouse movement event
     *  \note Please refer to https://docs.microsoft.com/zh-cn/windows/win32/learnwin32/mouse-movement
     */
    void    OnMouseMove(int pixelX, int pixelY, DWORD flags);
	/*!
	 *  \brief Handle mouse hover event
	 *  \note Please refer to https://docs.microsoft.com/zh-cn/windows/win32/learnwin32/other-mouse-operations
	 */
	void    OnMouseHover(int pixelX, int pixelY, DWORD flags);

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
		, m_pPreviousEllipse(nullptr)
        , m_bIsConfineCursor(false)
		, m_pMouseTrack(nullptr)
    {
        
    }
    virtual ~MainWindow() { }
public:
	virtual BOOL Create
	(
		PCTSTR lpWindowName,
		DWORD dwStyle,
		DWORD dwExStyle = 0,
		int x = CW_USEDEFAULT, int y = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT,
		HWND hWndParent = nullptr,
		HMENU hMenu = nullptr
	) override;
    virtual PCTSTR  ClassName() const override { return _T("Sample Window Class"); }
    virtual LRESULT HandleCommand(WPARAM wParam, LPARAM lParam) override;
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
	struct Ellipse          *m_pPreviousEllipse;
    EllipseList             m_list;
    bool                    m_bIsConfineCursor;
    MouseTrackEvents        *m_pMouseTrack;
};
