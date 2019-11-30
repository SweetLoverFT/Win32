#pragma once

#include <CommCtrl.h>
#include "BaseWindow.h"

class ToolTip
	: public BaseWindow<ToolTip>
{
public:
	ToolTip()
	{
		ZeroMemory(&m_ti, sizeof(TTTOOLINFO));
		m_ti.cbSize = TTTOOLINFOA_V2_SIZE;
		m_ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
		m_ti.hwnd = m_hWnd;
		m_ti.uId = reinterpret_cast<UINT_PTR>(m_hWnd);
		m_ti.hinst = GetModuleHandle(nullptr);
	}
	virtual ~ToolTip()
	{
		Destroy();
		if (m_hWnd)
			::DestroyWindow(m_hWnd);
	}
public:
	virtual void ShowTips(LPCTSTR text) = 0;
	virtual void HideTips() = 0;
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
	void Destroy();
	virtual PCTSTR  ClassName() const override { return TOOLTIPS_CLASS; }
	virtual LRESULT HandleCommand(WPARAM wParam, LPARAM lParam) override { return S_OK; };
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override
	{
		return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	};
protected:
	TOOLINFO m_ti;
	// Very important flag, used to prevent the thread crash
	bool m_bCanHide;
};
