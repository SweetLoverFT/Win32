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
        if (FAILED(::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
            ::PostQuitMessage(EXIT_FAILURE);
        InitializeDPIScale(pFactory);
        break;

    case WM_DESTROY:
        DiscardGraphicsResources();
        pFactory->Release();
        ::PostQuitMessage(EXIT_SUCCESS);
        break;

    case WM_PAINT:
        OnPaint();
        break;

    case WM_SIZE:
        OnResize();
        break;
    }
    return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

void MainWindow::CalculateLayout()
{
    if (pRenderTarget)
    {
        D2D1_SIZE_F size = pRenderTarget->GetSize();
        const float x = size.width / 2;
        const float y = size.height / 2;
        const float radius = min(x, y);
        ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
    }
}

HRESULT MainWindow::CreateGraphicsResources()
{
    HRESULT hr = S_OK;
    if (!pRenderTarget)
    {
        RECT rc = { };
        ::GetClientRect(m_hWnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
        hr = pFactory->CreateHwndRenderTarget
        (
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hWnd, size),
            &pRenderTarget
        );

        if (SUCCEEDED(hr))
        {
            const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0.0f);
            hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);
            if (SUCCEEDED(hr))
                CalculateLayout();
        }
    }
    return hr;
}

void MainWindow::DiscardGraphicsResources()
{
    pRenderTarget->Release();
    pBrush->Release();
}

void MainWindow::OnPaint()
{
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps = { };
        ::BeginPaint(m_hWnd, &ps);
        pRenderTarget->BeginDraw();
        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
        pRenderTarget->FillEllipse(ellipse, pBrush);
        hr = pRenderTarget->EndDraw();
        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
            DiscardGraphicsResources();
        ::EndPaint(m_hWnd, &ps);
    }
}

void MainWindow::OnResize()
{
    if (pRenderTarget)
    {
        RECT rc = { };
        ::GetClientRect(m_hWnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
        pRenderTarget->Resize(size);
        CalculateLayout();
        ::InvalidateRect(m_hWnd, nullptr, FALSE);
    }
}
