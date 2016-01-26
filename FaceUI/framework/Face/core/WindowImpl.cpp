#include "stdafx.h"

namespace Face
{
	WindowImpl::WindowImpl()
	{}

	WindowImpl::~WindowImpl()
	{}

	void WindowImpl::OnFinalMessage(HWND hWnd)
	{
		if (listener_)
		{
			listener_->OnFinalMessage(hWnd);
			WndsMgr::getInstance()->OnWndFinalMessage(GetWndClassName().Buffer());
		}
	}

	LRESULT WindowImpl::OnCreate(WPARAM wParam, LPARAM lParam, BOOL& handled)
	{
		auto setting = WndsMgr::getInstance()->GetWndConfig(GetWndClassName().Buffer());
		CHECK_ERROR(setting, L"Create window failed.");
		listener_ = setting->GetMsgListener();
		// TODO:开始创建Direct窗口

		listener_->OnWndCreated();
		return 0;
	}

	LRESULT WindowImpl::OnNcHitTest(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
		::ScreenToClient(*this, &pt);

		RECT rcClient;
		::GetClientRect(*this, &rcClient);

		return HTCLIENT;
	}

	LRESULT WindowImpl::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		MONITORINFO oMonitor = {};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
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

	LRESULT WindowImpl::OnSysCommand(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (wParam == SC_CLOSE)
		{
			bHandled = TRUE;
			SendMessage(WM_CLOSE);
		}

		listener_->OnSysCommand(wParam);
		return 0;
	}

	LRESULT WindowImpl::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;
		BOOL bHandled = TRUE;	
		switch (uMsg)
		{
			case WM_CREATE:
				lRes = OnCreate(wParam, lParam, bHandled);
				break;
			case WM_CLOSE:
			{	
				listener_->OnWndClose();
				lRes = 0;
				bHandled = FALSE;
				break;
			}
			case WM_DESTROY:
			{
				listener_->OnWndDestory();
				lRes = 0;
				bHandled = FALSE;
				break;
			}
			case WM_NCACTIVATE:
			{
				if (::IsIconic(this->GetHWND()))
					bHandled = FALSE;
				lRes = (wParam == 0) ? TRUE : FALSE;
				break;
			}
			case WM_NCCALCSIZE:
			case WM_NCPAINT:
			{	
				lRes = 0;
				break;
			}
			case WM_NCHITTEST:		
				lRes = OnNcHitTest(wParam, lParam, bHandled);
				break;
			case WM_GETMINMAXINFO:	
				lRes = OnGetMinMaxInfo(wParam, lParam, bHandled);
				break;
			case WM_SIZE:			
			{
				listener_->OnWndSize();
				lRes = 0;
				bHandled = FALSE;
				break;
			}
			case WM_CHAR:		
			{
				listener_->OnChar(wParam);
				lRes = 0;
				bHandled = FALSE;
				break;
			}
			case WM_SYSCOMMAND:		
			{
				lRes = OnSysCommand(wParam, lParam, bHandled);
				break;
			}
			case WM_KEYDOWN:		
			{
				listener_->OnKeyDown(wParam);
				lRes = 0;
				bHandled = FALSE;
				break;
			}
			case WM_LBUTTONUP:		
			case WM_LBUTTONDOWN:	
			case WM_KILLFOCUS:
			case WM_SETFOCUS:
			case WM_MOUSEWHEEL:
			case WM_MOUSEMOVE:	
			case WM_MOUSEHOVER:	
			{
				bHandled = FALSE;
				lRes = 0;
				break;
			}
			default:				
				bHandled = FALSE; 
				break;
		}

		if (bHandled)
		{
			return lRes;
		}

		lRes = listener_->HandleCustomMessage(uMsg, wParam, lParam, bHandled);
		if (bHandled)
			return lRes;


		return __super::HandleMessage(uMsg, wParam, lParam);
	}
}