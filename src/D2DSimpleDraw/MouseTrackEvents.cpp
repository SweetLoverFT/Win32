#include "stdafx.h"
#include "MouseTrackEvents.h"

void MouseTrackEvents::EnableTrack(HWND hWnd)
{
    if (!m_bIsMouseTracking)
    {
        m_hWnd = hWnd;
        // Enable mouse tracking.
        TRACKMOUSEEVENT tme =
        {
            sizeof(TRACKMOUSEEVENT),
            TME_HOVER,
            hWnd,
            HOVER_DEFAULT
        };
        ::TrackMouseEvent(&tme);
        m_bIsMouseTracking = true;
    }
}

void MouseTrackEvents::DisableTrack()
{
    TRACKMOUSEEVENT tme =
    {
        sizeof(TRACKMOUSEEVENT),
        TME_CANCEL | TME_HOVER,
        m_hWnd,
        HOVER_DEFAULT
    };
    ::TrackMouseEvent(&tme);
    m_bIsMouseTracking = false;
    m_hWnd = nullptr;
}

void MouseTrackEvents::Reset()
{
    m_bIsMouseTracking = false;
}
