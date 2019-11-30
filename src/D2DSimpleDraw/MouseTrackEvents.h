#pragma once

#include "ToolTip.h"

/*!
 * \class MouseTrackEvents
 * \brief Design this class to show a tool tip through class ToolTip when mouse hover on an ellipse
 * \author SweetLover
 * \date Oct the 20th, 2019
 */
class MouseTrackEvents
	: public ToolTip
{
public:
	MouseTrackEvents(HWND hWnd) : m_hWndParent(hWnd), m_bIsMouseTracking(false)
	{
		Create
		(
			ClassName(),
			NULL,
			NULL,
			CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT,
			hWnd
		);
	}
	virtual ~MouseTrackEvents()
	{
		Destroy();
	}
public:
	// These methods will actually call the interface provided by ToolTip class due to aggregation mode
	virtual void ShowTips(LPCTSTR text) override;
	virtual void HideTips() override;
public:
    void EnableTrack();
    void DisableTrack();
    void Reset();
private:
	HWND m_hWndParent;
	bool m_bIsMouseTracking;
private:
	static const UINT MAX_LENGTH;
};
