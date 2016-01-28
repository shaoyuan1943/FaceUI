#include "stdafx.h"

namespace Face
{
	WindowControl::WindowControl()
	{}

	WindowControl::~WindowControl()
	{}

	void WindowControl::OnWndCreated(HWND hwnd)
	{
		CHECK_ERROR(hwnd, L"HWND not be null.");

		hPaintWnd_ = hwnd;
	}

	void WindowControl::SetCapture()
	{
		::SetCapture(hPaintWnd_);
		isCapture_ = true;
	}

	void WindowControl::ReleaseCapture()
	{
		::ReleaseCapture();
		isCapture_ = false;
	}

	bool WindowControl::IsCapture()
	{
		return isCapture_;
	}
}