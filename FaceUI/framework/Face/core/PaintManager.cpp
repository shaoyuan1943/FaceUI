#include "stdafx.h"

namespace Face
{
	PaintMgr::PaintMgr()
	{}

	PaintMgr::~PaintMgr()
	{}

	bool PaintMgr::PreHandlerMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return false;
	}

	bool PaintMgr::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes)
	{

		return false;
	}

	void PaintMgr::OnWndCreated(HWND hwnd)
	{
		CHECK_ERROR(hwnd, L"HWND not be null.");

		hPaintWnd_ = hwnd;
		hPaintDC_ = ::GetDC(hwnd);
	}
}