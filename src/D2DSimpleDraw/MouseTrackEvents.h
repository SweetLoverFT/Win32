#pragma once

class MouseTrackEvents
{
public:
    MouseTrackEvents() : m_hWnd(nullptr), m_bIsMouseTracking(false) { }
public:
    void EnableTrack(HWND hwnd);
    void DisableTrack();
    void Reset();
private:
	HWND m_hWnd;
	bool m_bIsMouseTracking;
};
