#include "stdafx.h"
#include "MouseTrackEvents.h"

void MouseTrackEvents::ShowTips(LPCTSTR text)
{
	m_toolTip.ShowText(text);
}

void MouseTrackEvents::HideTips()
{
	m_toolTip.HideText();
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
            m_hWnd,
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
        m_hWnd,
        HOVER_DEFAULT
    };
    ::TrackMouseEvent(&tme);
    m_bIsMouseTracking = false;
}

void MouseTrackEvents::Reset()
{
    m_bIsMouseTracking = false;
}
