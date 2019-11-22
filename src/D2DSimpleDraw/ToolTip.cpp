#include "StdAfx.h"
#include "ToolTip.h"

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
