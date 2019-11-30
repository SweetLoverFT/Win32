#include "stdafx.h"
#include "MouseTrackEvents.h"

const UINT MouseTrackEvents::MAX_LENGTH = 100;

void MouseTrackEvents::ShowTips(LPCTSTR text)
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

void MouseTrackEvents::HideTips()
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

void MouseTrackEvents::EnableTrack()
{
    if (!m_bIsMouseTracking)
    {
        // Enable mouse tracking
        TRACKMOUSEEVENT tme =
        {
            sizeof(TRACKMOUSEEVENT),
            TME_HOVER,
            m_hWndParent,
            HOVER_DEFAULT
        };
        ::TrackMouseEvent(&tme);
        m_bIsMouseTracking = true;
    }
}

void MouseTrackEvents::DisableTrack()
{
	// Disable mouse tracking
    TRACKMOUSEEVENT tme =
    {
        sizeof(TRACKMOUSEEVENT),
        TME_CANCEL | TME_HOVER,
        m_hWndParent,
        HOVER_DEFAULT
    };
    ::TrackMouseEvent(&tme);
    m_bIsMouseTracking = false;
}

void MouseTrackEvents::Reset()
{
    m_bIsMouseTracking = false;
}
