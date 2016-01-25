#include "stdafx.h"

namespace Face
{
	MessageListener::MessageListener()
	{}

	MessageListener::~MessageListener()
	{}

	void MessageListener::OnFinalMessage(HWND hWnd)
	{

	}

	LRESULT MessageListener::OnClose(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT MessageListener::OnDestroy(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT MessageListener::OnNcActivate(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (::IsIconic(*wndOwner_)) 
			bHandled = FALSE;
		return (wParam == 0) ? TRUE : FALSE;
	}

	LRESULT MessageListener::OnNcCalcSize(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}

	LRESULT MessageListener::OnNcPaint(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}

	LRESULT MessageListener::OnNcHitTest(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return HTCAPTION;
	}

	LRESULT MessageListener::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		MONITORINFO oMonitor = {};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(wndOwner_->GetHWND(), MONITOR_DEFAULTTOPRIMARY), &oMonitor);
		Rect rcWork = oMonitor.rcWork;
		rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMaxPosition.x = rcWork.left;
		lpMMI->ptMaxPosition.y = rcWork.top;
		lpMMI->ptMaxSize.x = rcWork.GetWidth();
		lpMMI->ptMaxSize.y = rcWork.GetHeight();

		bHandled = FALSE;
		return 0;
	}

	LRESULT MessageListener::OnMouseWheel(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT MessageListener::OnMouseHover(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT MessageListener::OnSize(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT MessageListener::OnChar(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT MessageListener::OnSysCommand(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (wParam == SC_CLOSE)
		{
			bHandled = TRUE;
			wndOwner_->SendMessage(WM_CLOSE);
			return 0;
		}

		bHandled = FALSE;
		return 0;
	}

	LRESULT MessageListener::OnCreate(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;
		return 0;
	}

	LRESULT MessageListener::OnKeyDown(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT MessageListener::OnKillFocus(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT MessageListener::OnSetFocus(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT MessageListener::OnLButtonDown(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT MessageListener::OnLButtonUp(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT MessageListener::OnMouseMove(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT MessageListener::HandleCustomMessage(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}
}