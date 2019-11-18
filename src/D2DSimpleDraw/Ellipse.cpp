#include "stdafx.h"
#include "Ellipse.h"

void Ellipse::Draw(ID2D1RenderTarget *pRT, ID2D1SolidColorBrush *pBrush)
{
    pBrush->SetColor(m_color);
    pRT->FillEllipse(m_ellipse, pBrush);
    pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
    pRT->DrawEllipse(m_ellipse, pBrush, 1.0f);
}

bool Ellipse::HitTest(float x, float y)
{
    x -= m_ellipse.point.x;
    y -= m_ellipse.point.y;
    const float &a = m_ellipse.radiusX;
    const float &b = m_ellipse.radiusY;
    const float d = ((x * x) / (a * a)) + ((y * y) / (b * b));
    return d <= 1.0f;
}

int EllipseList::s_nColor[] =
{
    D2D1::ColorF::AliceBlue,
    D2D1::ColorF::AntiqueWhite,
    D2D1::ColorF::AliceBlue,
    D2D1::ColorF::AntiqueWhite,
    D2D1::ColorF::Aqua,
    D2D1::ColorF::Aquamarine,
    D2D1::ColorF::Azure,
    D2D1::ColorF::Beige,
    D2D1::ColorF::Bisque,
    // D2D1::ColorF::Black,
    D2D1::ColorF::BlanchedAlmond,
    D2D1::ColorF::Blue,
    D2D1::ColorF::BlueViolet,
    D2D1::ColorF::Brown,
    D2D1::ColorF::BurlyWood,
    D2D1::ColorF::CadetBlue,
    D2D1::ColorF::Chartreuse,
    D2D1::ColorF::Chocolate,
    D2D1::ColorF::Coral,
    D2D1::ColorF::CornflowerBlue,
    D2D1::ColorF::Cornsilk,
    D2D1::ColorF::Crimson,
    D2D1::ColorF::Cyan,
    D2D1::ColorF::DarkBlue,
    D2D1::ColorF::DarkCyan,
    D2D1::ColorF::DarkGoldenrod,
    D2D1::ColorF::DarkGray,
    D2D1::ColorF::DarkGreen,
    D2D1::ColorF::DarkKhaki,
    D2D1::ColorF::DarkMagenta,
    D2D1::ColorF::DarkOliveGreen,
    D2D1::ColorF::DarkOrange,
    D2D1::ColorF::DarkOrchid,
    D2D1::ColorF::DarkRed,
    D2D1::ColorF::DarkSalmon,
    D2D1::ColorF::DarkSeaGreen,
    D2D1::ColorF::DarkSlateBlue,
    D2D1::ColorF::DarkSlateGray,
    D2D1::ColorF::DarkTurquoise,
    D2D1::ColorF::DarkViolet,
    D2D1::ColorF::DeepPink,
    D2D1::ColorF::DeepSkyBlue,
    D2D1::ColorF::DimGray,
    D2D1::ColorF::DodgerBlue,
    D2D1::ColorF::Firebrick,
    D2D1::ColorF::FloralWhite,
    D2D1::ColorF::ForestGreen,
    D2D1::ColorF::Fuchsia,
    D2D1::ColorF::Gainsboro,
    D2D1::ColorF::GhostWhite,
    D2D1::ColorF::Gold,
    D2D1::ColorF::Goldenrod,
    D2D1::ColorF::Gray,
    D2D1::ColorF::Green,
    D2D1::ColorF::GreenYellow,
    D2D1::ColorF::Honeydew,
    D2D1::ColorF::HotPink,
    D2D1::ColorF::IndianRed,
    D2D1::ColorF::Indigo,
    D2D1::ColorF::Ivory,
    D2D1::ColorF::Khaki,
    D2D1::ColorF::Lavender,
    D2D1::ColorF::LavenderBlush,
    D2D1::ColorF::LawnGreen,
    D2D1::ColorF::LemonChiffon,
    D2D1::ColorF::LightBlue,
    D2D1::ColorF::LightCoral,
    D2D1::ColorF::LightCyan,
    D2D1::ColorF::LightGoldenrodYellow,
    D2D1::ColorF::LightGreen,
    D2D1::ColorF::LightGray,
    D2D1::ColorF::LightPink,
    D2D1::ColorF::LightSalmon,
    D2D1::ColorF::LightSeaGreen,
    D2D1::ColorF::LightSkyBlue,
    D2D1::ColorF::LightSlateGray,
    D2D1::ColorF::LightSteelBlue,
    D2D1::ColorF::LightYellow,
    D2D1::ColorF::Lime,
    D2D1::ColorF::LimeGreen,
    D2D1::ColorF::Linen,
    D2D1::ColorF::Magenta,
    D2D1::ColorF::Maroon,
    D2D1::ColorF::MediumAquamarine,
    D2D1::ColorF::MediumBlue,
    D2D1::ColorF::MediumOrchid,
    D2D1::ColorF::MediumPurple,
    D2D1::ColorF::MediumSeaGreen,
    D2D1::ColorF::MediumSlateBlue,
    D2D1::ColorF::MediumSpringGreen,
    D2D1::ColorF::MediumTurquoise,
    D2D1::ColorF::MediumVioletRed,
    D2D1::ColorF::MidnightBlue,
    D2D1::ColorF::MintCream,
    D2D1::ColorF::MistyRose,
    D2D1::ColorF::Moccasin,
    D2D1::ColorF::NavajoWhite,
    D2D1::ColorF::Navy,
    D2D1::ColorF::OldLace,
    D2D1::ColorF::Olive,
    D2D1::ColorF::OliveDrab,
    D2D1::ColorF::Orange,
    D2D1::ColorF::OrangeRed,
    D2D1::ColorF::Orchid,
    D2D1::ColorF::PaleGoldenrod,
    D2D1::ColorF::PaleGreen,
    D2D1::ColorF::PaleTurquoise,
    D2D1::ColorF::PaleVioletRed,
    D2D1::ColorF::PapayaWhip,
    D2D1::ColorF::PeachPuff,
    D2D1::ColorF::Peru,
    D2D1::ColorF::Pink,
    D2D1::ColorF::Plum,
    D2D1::ColorF::PowderBlue,
    D2D1::ColorF::Purple,
    D2D1::ColorF::Red,
    D2D1::ColorF::RosyBrown,
    D2D1::ColorF::RoyalBlue,
    D2D1::ColorF::SaddleBrown,
    D2D1::ColorF::Salmon,
    D2D1::ColorF::SandyBrown,
    D2D1::ColorF::SeaGreen,
    D2D1::ColorF::SeaShell,
    D2D1::ColorF::Sienna,
    D2D1::ColorF::Silver,
    D2D1::ColorF::SkyBlue,
    D2D1::ColorF::SlateBlue,
    D2D1::ColorF::SlateGray,
    D2D1::ColorF::Snow,
    D2D1::ColorF::SpringGreen,
    D2D1::ColorF::SteelBlue,
    D2D1::ColorF::Tan,
    D2D1::ColorF::Teal,
    D2D1::ColorF::Thistle,
    D2D1::ColorF::Tomato,
    D2D1::ColorF::Turquoise,
    D2D1::ColorF::Violet,
    D2D1::ColorF::Wheat,
    // D2D1::ColorF::White = 0xFFFFFF,
    D2D1::ColorF::WhiteSmoke,
    D2D1::ColorF::Yellow,
    D2D1::ColorF::YellowGreen,
};

struct Ellipse* EllipseList::InsertEllipse(float x, float y)
{
    struct Ellipse ellipse;
    int index = ::rand() % (sizeof(s_nColor) / sizeof(int));
    ellipse.m_ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), 0.0f, 0.0f);
    ellipse.m_colorValue = s_nColor[index];
    ellipse.m_color = D2D1::ColorF(s_nColor[index]);
    m_list->push_back(ellipse);
    return &*m_list->rbegin();
}

struct Ellipse* EllipseList::HitTest(float x, float y)
{
    for (auto iter = m_list->rbegin(); iter != m_list->rend(); ++iter)
        if (iter->HitTest(x, y))
            return &*iter;

    return nullptr;
}

void EllipseList::DrawAll(ID2D1RenderTarget *pRT, ID2D1SolidColorBrush *pBrush)
{
    for (auto iter = m_list->begin(); iter != m_list->end(); ++iter)
        iter->Draw(pRT, pBrush);
}
