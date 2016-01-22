#include "stdafx.h"

namespace Face
{
	FaceWindowImpl::FaceWindowImpl()
	{}

	FaceWindowImpl::~FaceWindowImpl()
	{}

	void FaceWindowImpl::OnFinalMessage(HWND hWnd)
	{
		if (listener_)
		{
			listener_->OnFinalMessage(hWnd);
		}
	}

	LRESULT FaceWindowImpl::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;
		BOOL bHandled = TRUE;
		WString& wndClassName = GetWndClassName();
		switch (uMsg)
		{
		case WM_CREATE:	
		{
			if (listener_ == nullptr)
			{
				listener_ = FaceWndsMgr::getInstance()->GetMessageListener(wndClassName.Buffer());
				listener_->SetWindowImpl(this);
				auto wo = FaceWndsMgr::getInstance()->GetWindowObject(wndClassName.Buffer());
				wo->wnd = this;
			}
			listener_->OnCreate(uMsg, wParam, lParam, bHandled);
		}
			break;
		case WM_CLOSE:		
			listener_->OnClose(uMsg, wParam, lParam, bHandled);
			break;
		case WM_DESTROY:
			listener_->OnDestroy(uMsg, wParam, lParam, bHandled);
			break;
		case WM_NCACTIVATE:		
			listener_->OnNcActivate(uMsg, wParam, lParam, bHandled);
			break;
		case WM_NCCALCSIZE:		
			listener_->OnNcCalcSize(uMsg, wParam, lParam, bHandled);
			break;
		case WM_NCPAINT:		
			listener_->OnNcPaint(uMsg, wParam, lParam, bHandled);
			break;
		case WM_NCHITTEST:		
			listener_->OnNcHitTest(uMsg, wParam, lParam, bHandled);
			break;
		case WM_GETMINMAXINFO:	
			listener_->OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled);
			break;
		case WM_MOUSEWHEEL:		
			listener_->OnMouseWheel(uMsg, wParam, lParam, bHandled);
			break;
		case WM_SIZE:			
			listener_->OnSize(uMsg, wParam, lParam, bHandled);
			break;
		case WM_CHAR:		
			listener_->OnChar(uMsg, wParam, lParam, bHandled);
			break;
		case WM_SYSCOMMAND:		
			listener_->OnSysCommand(uMsg, wParam, lParam, bHandled);
			break;
		case WM_KEYDOWN:		
			listener_->OnKeyDown(uMsg, wParam, lParam, bHandled);
			break;
		case WM_KILLFOCUS:	
			listener_->OnKillFocus(uMsg, wParam, lParam, bHandled);
			break;
		case WM_SETFOCUS:		
			listener_->OnSetFocus(uMsg, wParam, lParam, bHandled);
			break;
		case WM_LBUTTONUP:		
			listener_->OnLButtonUp(uMsg, wParam, lParam, bHandled);
			break;
		case WM_LBUTTONDOWN:	
			listener_->OnLButtonDown(uMsg, wParam, lParam, bHandled);
			break;
		case WM_MOUSEMOVE:	
			listener_->OnMouseMove(uMsg, wParam, lParam, bHandled);
			break;
		case WM_MOUSEHOVER:	
			listener_->OnMouseHover(uMsg, wParam, lParam, bHandled);
			break;
		default:				
			bHandled = FALSE; 
			break;
		}

		return __super::HandleMessage(uMsg, wParam, lParam);
	}
}