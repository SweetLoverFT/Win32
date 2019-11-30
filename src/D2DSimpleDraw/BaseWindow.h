#pragma once

template <class DERIVED_TYPE>
class BaseWindow
{
public:
    BaseWindow() { }
    virtual ~BaseWindow() { }
public:
    HWND Window() const { return m_hWnd; }
	virtual BOOL Create
    (
        PCTSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT, int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT,
        HWND hWndParent = nullptr,
        HMENU hMenu = nullptr
    ) = 0;
public:
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
    virtual PCTSTR  ClassName() const = 0;
	/*!
	 *  \brief Handle user-defined commands, some of them are keyboard and mouse actions
	 *  \note Please refer to https://docs.microsoft.com/zh-cn/windows/win32/learnwin32/mouse-clicks
	 */
	virtual LRESULT HandleCommand(WPARAM wParam, LPARAM lParam) = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
protected:
    HWND m_hWnd;
};

template <class DERIVED_TYPE>
LRESULT BaseWindow<DERIVED_TYPE>::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    DERIVED_TYPE *pThis = nullptr;
    if (uMsg == WM_NCCREATE)
    {
        LPCREATESTRUCT pCreate = reinterpret_cast<LPCREATESTRUCT>(lParam);
        pThis = reinterpret_cast<DERIVED_TYPE*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
        pThis->m_hWnd = hWnd;
    }
    else
        pThis = reinterpret_cast<DERIVED_TYPE*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    if (pThis)
        return pThis->HandleMessage(uMsg, wParam, lParam);
    else
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
