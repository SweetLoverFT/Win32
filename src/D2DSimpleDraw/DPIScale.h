#pragma once

#include "stdafx.h"
#include <d2d1.h>

/*!
 *  In Direct2D, we use DIPs (Device-independent pixels) instead of DPI (Dots per inch).
 *  Therefore, the units of measurement are consistent for both text and drawing,
 *  regardless of the current DPI setting.
 *  But for GDI, mouse and window coordinate are still given in physical pixels.
 *  Link: https://docs.microsoft.com/zh-cn/windows/desktop/LearnWin32/dpi-and-device-independent-pixels.
 */
class DPIScale
{
private:
    static double scaleX;
    static double scaleY;
public:
    static void Initialize(ID2D1Factory *pFactory)
    {
        FLOAT dpiX, dpiY;
        pFactory->GetDesktopDpi(&dpiX, &dpiY);
        scaleX = dpiX / 96.0f;
        scaleY = dpiY / 96.0f;
    }

    template <typename T>
    static D2D1_POINT_2F PixelsToDips(T x, T y)
    {
        return D2D1::Point2F(static_cast<double>(x) / scaleX, static_cast<double>(y) / scaleY);
    }

    template <typename T>
    static D2D1_POINT_2F DipsToPixels(T x, T y)
    {
        return D2D1::Point2F(static_cast<double>(x) * scaleX, static_cast<double>(y) * scaleY);
    }
};

double DPIScale::scaleX = 1.0f;
double DPIScale::scaleY = 1.0f;
