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

		listener_->OnCreate(wParam, lParam, handled);
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
			lRes = listener_->OnClose(wParam, lParam, bHandled);
			break;
		case WM_DESTROY:
			lRes = listener_->OnDestroy(wParam, lParam, bHandled);
			break;
		case WM_NCACTIVATE:		
			lRes = listener_->OnNcActivate(wParam, lParam, bHandled);
			break;
		case WM_NCCALCSIZE:		
			lRes = listener_->OnNcCalcSize(wParam, lParam, bHandled);
			break;
		case WM_NCPAINT:		
			lRes = listener_->OnNcPaint(wParam, lParam, bHandled);
			break;
		case WM_NCHITTEST:		
			lRes = listener_->OnNcHitTest(wParam, lParam, bHandled);
			break;
		case WM_GETMINMAXINFO:	
			lRes = listener_->OnGetMinMaxInfo(wParam, lParam, bHandled);
			break;
		case WM_MOUSEWHEEL:		
			lRes = listener_->OnMouseWheel(wParam, lParam, bHandled);
			break;
		case WM_SIZE:			
			lRes = listener_->OnSize(wParam, lParam, bHandled);
			break;
		case WM_CHAR:		
			lRes = listener_->OnChar(wParam, lParam, bHandled);
			break;
		case WM_SYSCOMMAND:		
			lRes = listener_->OnSysCommand(wParam, lParam, bHandled);
			break;
		case WM_KEYDOWN:		
			lRes = listener_->OnKeyDown(wParam, lParam, bHandled);
			break;
		case WM_KILLFOCUS:	
			lRes = listener_->OnKillFocus(wParam, lParam, bHandled);
			break;
		case WM_SETFOCUS:		
			lRes = listener_->OnSetFocus(wParam, lParam, bHandled);
			break;
		case WM_LBUTTONUP:		
			listener_->OnLButtonUp(wParam, lParam, bHandled);
			break;
		case WM_LBUTTONDOWN:	
			listener_->OnLButtonDown(wParam, lParam, bHandled);
			break;
		case WM_MOUSEMOVE:	
			lRes = listener_->OnMouseMove(wParam, lParam, bHandled);
			break;
		case WM_MOUSEHOVER:	
			lRes = listener_->OnMouseHover(wParam, lParam, bHandled);
			break;
		default:				
			bHandled = FALSE; 
			break;
		}

		if (bHandled)
		{
			return lRes;
		}

		lRes = listener_->HandleCustomMessage(wParam, lParam, bHandled);
		if (bHandled)
			return lRes;


		return __super::HandleMessage(uMsg, wParam, lParam);
	}
}