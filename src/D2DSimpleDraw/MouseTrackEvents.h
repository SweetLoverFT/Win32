#pragma once

#include "ToolTip.h"

/*!
 * \class MouseTrackEvents
 * \brief Design this class to show a tool tip through class ToolTip when mouse hover on an ellipse
 * \author SweetLover
 * \date Oct the 20th, 2019
 */
class MouseTrackEvents
{
public:
	MouseTrackEvents(HWND hWnd) : m_hWnd(hWnd), m_bIsMouseTracking(false)
	{
		m_toolTip.Create
		(
			m_toolTip.ClassName(),
			NULL,
			NULL,
			CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT,
			hWnd
		);
	}
	~MouseTrackEvents()
	{
		m_toolTip.Destroy();
	}
public:
	// These methods will actually call the interface provided by ToolTip class due to aggregation mode
	void ShowTips(LPCTSTR text);
	void HideTips();
public:
    void EnableTrack();
    void DisableTrack();
    void Reset();
private:
	HWND m_hWnd;
	// Think in design pattern, will it be better to use inheritance instead of aggregation mode?
	ToolTip m_toolTip;
	bool m_bIsMouseTracking;
};
