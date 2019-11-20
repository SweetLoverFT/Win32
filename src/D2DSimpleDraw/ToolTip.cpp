#include "StdAfx.h"
#include "ToolTip.h"

const UINT ToolTip::MAX_LENGTH = 100;

void ToolTip::ShowText(LPCTSTR text)
{
	if (m_hWnd)
	{
		m_ti.lpszText = const_cast<LPTSTR>(text);
		SendMessage(m_hWnd, TTM_ADDTOOL, NULL, reinterpret_cast<LPARAM>(&m_ti));
		// Add support for multi-line text, use "\n" in text to start a new line
		SendMessage(m_hWnd, TTM_SETMAXTIPWIDTH, NULL, MAX_LENGTH);
		SendMessage(m_hWnd, TTM_TRACKACTIVATE, TRUE, reinterpret_cast<LPARAM>(&m_ti));
		m_bCanHide = true;
	}
}

void ToolTip::HideText()
{
	if (m_hWnd && m_bCanHide)
	{
		m_bCanHide = false;
		SendMessage(m_hWnd, TTM_TRACKACTIVATE, FALSE, reinterpret_cast<LPARAM>(&m_ti));
		// A "TTM_ADDTOOL" message corresponds to a "TTM_DELTOOL" message,
		// a ToolTip's object will crash if send "TTM_DELTOOL" twice at the same time
		SendMessage(m_hWnd, TTM_DELTOOL, 0, reinterpret_cast<LPARAM>(&m_ti));
	}
}

BOOL ToolTip::Create
(
	PCTSTR lpWindowName,
	DWORD dwStyle,
	DWORD dwExStyle/* = 0*/,
	int x/* = CW_USEDEFAULT*/, int y/* = CW_USEDEFAULT*/,
	int nWidth/* = CW_USEDEFAULT*/, int nHeight/* = CW_USEDEFAULT*/,
	HWND hWndParent/* = nullptr*/,
	HMENU hMenu/* = nullptr*/
)
{
	m_hWnd = CreateWindowEx
	(
		NULL,
		TOOLTIPS_CLASS,
		NULL,
		WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP | TTS_BALLOON,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		hWndParent,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);

	return m_hWnd ? TRUE : FALSE;
}

void ToolTip::Destroy()
{
	if (m_hWnd)
	{
		SendMessage(m_hWnd, TTM_TRACKACTIVATE, FALSE, reinterpret_cast<LPARAM>(&m_ti));
		SendMessage(m_hWnd, TTM_DELTOOL, 0, reinterpret_cast<LPARAM>(&m_ti));
		DestroyWindow(m_hWnd);
		m_hWnd = nullptr;
	}
}
