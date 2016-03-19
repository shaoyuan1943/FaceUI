#include "stdafx.h"
#include "match.hpp"

namespace Face
{ 
	WindowControl::WindowControl()
	{}

	WindowControl::~WindowControl()
	{}

	void WindowControl::SetWndHWND(HWND hwnd)
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

	void WindowControl::SetWindowSize(int cx, int cy)
	{
		wndSize_.cx = cx;
		wndSize_.cy = cy;

		if (hPaintWnd_)
		{
			::SetWindowPos(hPaintWnd_, nullptr, 0, 0, cx, cy, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
		}
	}

	const Size* WindowControl::GetWindowSize()
	{
		return &wndSize_;
	}

	void WindowControl::SetAttribute(LPCTSTR key, LPCTSTR value)
	{
		Match(key)
		{
			Case(L"size")
			{
				Utils::ToSize(value, &wndSize_);
				SetWindowSize(wndSize_.cx, wndSize_.cy);
			}
			Case(L"sizebox")
			{
				Utils::ToRect(value, &dragBorderSize_);
			}
			Case(L"caption")
			{
				Utils::ToRect(value, &caption_);
			}
			Case(L"minisize")
			{
				Utils::ToSize(value, &minSize_);
			}
			Case(L"maxisze")
			{
				Utils::ToSize(value, &maxSize_);
			}
			Case(L"roundcorner")
			{
				Utils::ToSize(value, &roundCorner_);
			}
		}
		EndMatch
	}
}