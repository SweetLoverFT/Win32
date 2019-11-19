#include "stdafx.h"
#include "DPIScale.h"
#include "MainWindow.h"
#include <CommCtrl.h>

BOOL MainWindow::Create
(
	PCTSTR lpWindowName,
	DWORD dwStyle,
	DWORD dwExStyle,
	int x, int y,
	int nWidth, int nHeight,
	HWND hWndParent,
	HMENU hMenu
)
{
	WNDCLASS wc = { 0 };
	wc.style = CS_DBLCLKS;  // Enable to handle double-click event
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = ClassName();
	RegisterClass(&wc);

	m_hWnd = CreateWindowEx
	(
		dwExStyle,
		ClassName(),
		lpWindowName,
		dwStyle,
		x, y,
		nWidth, nHeight,
		hWndParent,
		hMenu,
		GetModuleHandle(nullptr),
		this
	);

	return (m_hWnd ? TRUE : FALSE);
}

LRESULT MainWindow::HandleCommand(WPARAM wParam, LPARAM lParam)
{
	LRESULT hr = S_OK;
    switch (WORD wCmd = LOWORD(wParam))
    {
    case ID_DRAW_MODE:
    case ID_DRAG_MODE:
    case ID_SELECT_MODE:
		hr = SetMode(wCmd);
		break;
	case ID_SWITCH_MODE:
		hr = SetMode(m_wMode % 3 + ID_DRAG_MODE);
		break;
	case ID_CONFINE_CURSOR:
		hr = ConfineCursor();
		break;
	}
	return hr;
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
		// As for customized commands and messages, it's unnecessary to call DefWindowProc
        return HandleCommand(wParam, lParam);

    case WM_CREATE:
        OnCreate();
        break;

    case WM_DESTROY:
        OnDestroy();
        break;

    case WM_SIZE:
        OnResize();
        break;

    case WM_PAINT:
        OnPaint();
        break;

/*
    case WM_SETCURSOR:
        // Set the cursor only when mouse is inside the client area
        if (LOWORD(lParam) == HTCLIENT)
        {
            / * If your application must set the cursor while it is in a window, make sure the class cursor 
             * for the specified window's class is set to NULL. If the class cursor is not NULL, the system
             * restores the class cursor each time the mouse is moved.
             * https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-setcursor
             * /
            ::SetCursor(m_hCursor);
            return TRUE;
        }
        break;
*/

    case WM_MOUSEMOVE:
        OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<DWORD>(wParam));
		break;

	case WM_MOUSEHOVER:
		OnMouseHover(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<DWORD>(wParam));
		break;

    case WM_LBUTTONDOWN:
        OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<DWORD>(wParam));
		break;

    case WM_LBUTTONUP:
        OnLButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<DWORD>(wParam));
        break;

    // For keyboard messages please refer the link below
    // https://docs.microsoft.com/zh-cn/windows/win32/learnwin32/keyboard-input
    // Beware to handle Input Method Editors for WM_IME_CHAR message

    }
    return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

/************************************************************************/
/* Extra functions                                                      */
/************************************************************************/

void MainWindow::CalculateLayout()
{
    
}

HRESULT MainWindow::CreateGraphicsResources()
{
    HRESULT hr = S_OK;
    if (!m_pRenderTarget)
    {
        RECT rc = { };
        ::GetClientRect(m_hWnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
        hr = m_pFactory->CreateHwndRenderTarget
        (
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hWnd, size),
            &m_pRenderTarget
        );

        if (SUCCEEDED(hr))
        {
            const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0.0f);
            hr = m_pRenderTarget->CreateSolidColorBrush(color, &m_pBrush);
        }
    }
    return hr;
}

void MainWindow::DiscardGraphicsResources()
{
    m_pRenderTarget->Release();
    m_pBrush->Release();
}

/************************************************************************/
/* User-defined commands                                                */
/************************************************************************/

HRESULT MainWindow::SetMode(WORD wCmd)
{
    LPTSTR cursorName = nullptr;
    LPCTSTR currentMode = nullptr;
    switch (wCmd)
    {
    case ID_DRAW_MODE:
        cursorName = IDC_CROSS;
        currentMode = _T("Draw mode\n");
        break;
    case ID_DRAG_MODE:
        cursorName = IDC_HAND;
        currentMode = _T("Drag mode\n");
        break;
    case ID_SELECT_MODE:
        cursorName = IDC_ARROW;
        currentMode = _T("Select mode\n");
        break;
    }

    // For cursor image, please refer to the link below
    // https://docs.microsoft.com/zh-cn/windows/win32/learnwin32/setting-the-cursor-image
    // Beware to custom cursor and strategy to handle WM_SETCURSOR by DefWindowProc
    m_wMode = wCmd;
    m_hCursor = LoadCursor(nullptr, cursorName);
    // This will generate WM_SETCURSOR
    ::SetCursor(m_hCursor);
    OutputDebugString(currentMode);

    return S_OK;
}

HRESULT MainWindow::ConfineCursor()
{
    m_bIsConfineCursor = !m_bIsConfineCursor;
    if (m_bIsConfineCursor)
    {
        // Get the window client area.
        RECT rc = { };
        ::GetClientRect(m_hWnd, &rc);

        // Convert the client area to screen coordinates.
        POINT pt[] =
        {
            // Bugs from Windows 10: Sometimes the mouse can click on the border,
            // this leads a failure to confine the cursor when the cursor click the top-right
            // close button or resize the window on the right border
            { rc.left, rc.top },
            { rc.right, rc.bottom },
        };
        ::ClientToScreen(m_hWnd, &pt[0]);
        ::ClientToScreen(m_hWnd, &pt[1]);
        ::SetRect(&rc, pt[0].x, pt[0].y, pt[1].x, pt[1].y);

        // Confine the cursor.
        ::ClipCursor(&rc);
    }
    else
    {
        // Restore
        ::ClipCursor(nullptr);
    }
    return S_OK;
}

/************************************************************************/
/* Windows messages                                                     */
/************************************************************************/

void MainWindow::OnResize()
{
    if (m_pRenderTarget)
    {
        RECT rc = { };
        ::GetClientRect(m_hWnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
        m_pRenderTarget->Resize(size);
        CalculateLayout();
        ::InvalidateRect(m_hWnd, nullptr, FALSE);
    }
}

void MainWindow::OnCreate()
{
    if (FAILED(::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory)))
        ::PostQuitMessage(EXIT_FAILURE);
    DPIScale::Initialize(m_pFactory);
}

void MainWindow::OnDestroy()
{
	m_mouseTrack.DisableTrack();
    DiscardGraphicsResources();
    m_pFactory->Release();
    ::PostQuitMessage(EXIT_SUCCESS);
}

// In game development, this is called "render scene". Sometimes, keyboard event will be
// handled later according to current action status in Real-time ACT Game. e.g, a boxer
// may punch somebody, but he could make another punch after this punch, this means the
// keyboard event handler is associated with the rendered scene.
void MainWindow::OnPaint()
{
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps = { };
        ::BeginPaint(m_hWnd, &ps);
        m_pRenderTarget->BeginDraw();
        m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
        m_list.DrawAll(m_pRenderTarget, m_pBrush);
        hr = m_pRenderTarget->EndDraw();
        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
            DiscardGraphicsResources();
        ::EndPaint(m_hWnd, &ps);
    }
}

void MainWindow::OnMouseMove(int pixelX, int pixelY, DWORD flags)
{
    const D2D1_POINT_2F pt = DPIScale::PixelsToDips(pixelX, pixelY);
    if (flags & MK_LBUTTON)
    {
        if (ID_DRAW_MODE == m_wMode)
        {
            // Change current ellipse
            m_pEllipse->m_ellipse.radiusX = fabs(pt.x - m_ptMouse.x);
            m_pEllipse->m_ellipse.radiusY = fabs(pt.y - m_ptMouse.y);
        }
        else if (ID_DRAG_MODE == m_wMode)
        {
            // Move the ellipse
            m_pEllipse->m_ellipse.point.x += pt.x - m_ptMouse.x;
            m_pEllipse->m_ellipse.point.y += pt.y - m_ptMouse.y;
            m_ptMouse = pt;
        }        
        ::InvalidateRect(m_hWnd, nullptr, FALSE);
    }
	else
		m_mouseTrack.EnableTrack(m_hWnd);
}

// It will be better to use state machine to switch mode
// Please refer to https://docs.microsoft.com/zh-cn/windows/win32/learnwin32/user-input--extended-example
void MainWindow::OnLButtonDown(int pixelX, int pixelY, DWORD flags)
{
    const D2D1_POINT_2F pt = m_ptMouse = DPIScale::PixelsToDips(pixelX, pixelY);
    if (ID_SELECT_MODE == m_wMode)
    {
        // Pick an ellipse from top to bottom
        m_pEllipse = m_list.HitTest(pt.x, pt.y);
        if (m_pEllipse)
            SetMode(ID_DRAG_MODE);
        else
        {
            const POINT point = { pt.x, pt.y };
            // Judge the mouse gesture to check whether it is a drag operation
            if (TRUE == ::DragDetect(m_hWnd, point))
            {
                SetMode(ID_DRAW_MODE);
                // Start a new ellipse.
                m_pEllipse = m_list.InsertEllipse(pt.x, pt.y);
            }
        }
    }
    // Capture mouse trails even it moves outside the window
    ::SetCapture(m_hWnd);
    // Generate WM_PAINT message
    ::InvalidateRect(m_hWnd, nullptr, FALSE);
}

void MainWindow::OnLButtonUp(int pixelX, int pixelY, DWORD flags)
{
    SetMode(ID_SELECT_MODE);
    // Stop capturing mouse trails
    ::ReleaseCapture();
    // Generate WM_PAINT message
    ::InvalidateRect(m_hWnd, nullptr, FALSE);
}

void MainWindow::OnMouseHover(int pixelX, int pixelY, DWORD flags)
{
    // Originally, we'd like to show a tool tip used to show the information for specific ellipse
	OutputDebugString(_T("Mouse hover!\n"));
	m_mouseTrack.Reset();
}
