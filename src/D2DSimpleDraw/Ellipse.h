#pragma once

#include <d2d1.h>
#include <list>
#include <ctime>
#include <cmath>

struct Ellipse
{
    D2D1_ELLIPSE    m_ellipse;
    D2D1_COLOR_F    m_color;
    UINT            m_colorValue;

    void Draw(ID2D1RenderTarget *pRT, ID2D1SolidColorBrush *pBrush);
    bool HitTest(float x, float y);
};

class EllipseList
{
private:
    static int s_nColor[];
private:
    std::list<struct Ellipse> *m_list;
public:
    EllipseList()
        // Note: Never allocate STL buffer at constructing time, maybe fail.
        // Error: m_list(new std::list<struct Ellipse>())
        : m_list(nullptr)
    {
        ::srand(time(nullptr));
        m_list = new std::list<struct Ellipse>();
    }
    ~EllipseList()
    {
        m_list->clear();
        delete m_list;
    }
public:
    struct Ellipse* InsertEllipse(float x, float y);
    struct Ellipse* HitTest(float x, float y);
    void DrawAll(ID2D1RenderTarget *pRT, ID2D1SolidColorBrush *pBrush);
};
