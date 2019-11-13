#include "stdafx.h"
#include "MainWindow.h"

double MainWindow::s_DPIScaleX = 0.0;
double MainWindow::s_DPIScaleY = 0.0;

void MainWindow::InitializeDPIScale(ID2D1Factory *pFactory)
{
    float dpiX = 0.0f, dpiY = 0.0f;
    pFactory->GetDesktopDpi(&dpiX, &dpiY);
    s_DPIScaleX = dpiX / 96.0;
    s_DPIScaleY = dpiY / 96.0;
}

void MainWindow::InitializeDPIScale(HWND hwnd)
{
    HDC hdc = ::GetDC(hwnd);
    s_DPIScaleX = ::GetDeviceCaps(hdc, LOGPIXELSX) / 96.0;
    s_DPIScaleY = ::GetDeviceCaps(hdc, LOGPIXELSY) / 96.0;
    ::ReleaseDC(hwnd, hdc);
}

void MainWindow::PixelsToDips(int x, int y, double *pX, double * pY)
{
    *pX = x / s_DPIScaleX;
    *pY = y / s_DPIScaleY;
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        if (FAILED(::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory)))
            ::PostQuitMessage(EXIT_FAILURE);
        InitializeDPIScale(m_pFactory);
        // As for function "SetTimer": The exist timer will be replaced if the timer ID is the same.
        // Otherwise, there will be a new timer. Notice the window must be owned by th calling thread.
        ::SetTimer(m_hWnd, ID_TIMER_UPDATE, DELAY_TIME, nullptr);
        break;

    case WM_DESTROY:
        ::KillTimer(m_hWnd, ID_TIMER_UPDATE);
        DiscardGraphicsResources();
        m_pFactory->Release();
        ::PostQuitMessage(EXIT_SUCCESS);
        break;

    case WM_PAINT:
        OnPaint();
        break;

    case WM_TIMER:
        // PostMessage only post this message into message queue, but never wait it done
        ::PostMessage(m_hWnd, WM_PAINT, NULL, NULL);
        // UpdateWindow never generates WM_PAINT, it just change the priority for existed WM_PAINT
        ::UpdateWindow(m_hWnd);
        break;

    case WM_SIZE:
        OnResize();
        break;
    }
    return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

void MainWindow::CalculateLayout()
{
    if (m_pRenderTarget)
    {
        D2D1_SIZE_F size = m_pRenderTarget->GetSize();
        const float x = size.width / 2;
        const float y = size.height / 2;
        const float radius = min(x, y);
        m_ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
    }
}

void MainWindow::DrawClockHand(float fHandLength, float fAngle, float fStrokeWidth)
{
    m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(fAngle, m_ellipse.point));

    // endPoint defines one end of the hand.
    D2D_POINT_2F endPoint = D2D1::Point2F
    (
        m_ellipse.point.x,
        m_ellipse.point.y - (m_ellipse.radiusY * fHandLength)
    );

    // Draw a line from the center of the ellipse to endPoint.
    m_pRenderTarget->DrawLine(m_ellipse.point, endPoint, m_pBrushBlack, fStrokeWidth);
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
            D2D1_STROKE_STYLE_PROPERTIES properties =
            {
                D2D1_CAP_STYLE_TRIANGLE,
                D2D1_CAP_STYLE_ROUND,
                D2D1_CAP_STYLE_ROUND,
                D2D1_LINE_JOIN_MITER,
                1.0f,
                D2D1_DASH_STYLE_SOLID,
                10.0f
            };
            hr = m_pFactory->CreateStrokeStyle(properties, nullptr, 0, &m_pStroke);
            if (SUCCEEDED(hr))
            {
                const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0.0f);
                hr = m_pRenderTarget->CreateSolidColorBrush(color, &m_pBrush);
                if (SUCCEEDED(hr))
                {
                    const D2D1_COLOR_F color = D2D1::ColorF(0.0f, 0.0f, 0.0f);
                    hr = m_pRenderTarget->CreateSolidColorBrush(color, &m_pBrushBlack);
                }
            }
        }
    }
    return hr;
}

void MainWindow::DiscardGraphicsResources()
{
    m_pRenderTarget->Release();
    m_pBrush->Release();
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
        m_pRenderTarget->FillEllipse(m_ellipse, m_pBrush);
        // m_pRenderTarget->DrawEllipse(m_ellipse, m_pBrushBlack);
        // Draw hour hand and minute hand
        SYSTEMTIME time = { };
        ::GetLocalTime(&time);
        const float fHourAngle = (360.0f / 12) * (time.wHour) + (time.wMinute * 0.5f);
        const float fMinuteAngle = (360.0f / 60) * (time.wMinute);
        const float fSecondAngle = (360.0f / 60) * (time.wSecond);
        DrawClockHand(0.6f, fHourAngle, 6);
        DrawClockHand(0.85f, fMinuteAngle, 4);
        DrawClockHand(1.0f, fSecondAngle, 2);
        // Restore the identity transformation.
        m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        hr = m_pRenderTarget->EndDraw();
        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
            DiscardGraphicsResources();
        ::EndPaint(m_hWnd, &ps);
    }
}

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
