#include "stdafx.h"
#include "DPIScale.h"
#include "MainWindow.h"

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        if (FAILED(::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory)))
            ::PostQuitMessage(EXIT_FAILURE);
        DPIScale::Initialize(m_pFactory);
        break;

    case WM_DESTROY:
        DiscardGraphicsResources();
        m_pFactory->Release();
        ::PostQuitMessage(EXIT_SUCCESS);
        break;

    case WM_PAINT:
        OnPaint();
        break;

    case WM_SIZE:
        OnResize();
        break;

    case WM_LBUTTONDOWN:
        OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
        return 0;

    case WM_LBUTTONUP:
        OnLButtonUp();
        return 0;

    case WM_MOUSEMOVE:
        OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
        return 0;
    }
    return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

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

void MainWindow::OnLButtonDown(int pixelX, int pixelY, DWORD flags)
{
    // Capture mouse trails even it moves outside the window
    ::SetCapture(m_hWnd);
    m_ellipse.point = m_ptMouse = DPIScale::PixelsToDips(pixelX, pixelY);
    m_ellipse.radiusX = m_ellipse.radiusY = 1.0f;
    // Generate WM_PAINT message
    ::InvalidateRect(m_hWnd, nullptr, FALSE);
}

void MainWindow::OnLButtonUp()
{
    // Stop capturing mouse trails
    ::ReleaseCapture();
}

void MainWindow::OnMouseMove(int pixelX, int pixelY, DWORD flags)
{
    if (flags & MK_LBUTTON)
    {
        const D2D1_POINT_2F dips = DPIScale::PixelsToDips(pixelX, pixelY);

        const float width = (dips.x - m_ptMouse.x) / 2;
        const float height = (dips.y - m_ptMouse.y) / 2;
        const float x1 = m_ptMouse.x + width;
        const float y1 = m_ptMouse.y + height;

        // Set new ellipse
        m_ellipse = D2D1::Ellipse(D2D1::Point2F(x1, y1), width, height);
        ::InvalidateRect(m_hWnd, nullptr, FALSE);
    }
}
