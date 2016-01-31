#include "stdafx.h"

namespace Face
{
	WindowImpl::WindowImpl()
	{}

	WindowImpl::~WindowImpl()
	{}
	 
	void WindowImpl::OnFinalMessage(HWND hWnd)
	{

	}
	
	WindowControl* WindowImpl::GetWndControl()
	{
		return &_wc_;
	}

	void WindowImpl::OnCreate(WPARAM wParam, LPARAM lParam)
	{
		auto setting = WndsMgr::getInstance()->GetWndConfig(GetWndClassName().Buffer());
		CHECK_ERROR(setting, L"Create window failed.");
		
		_wc_.OnWndCreated(this->GetHWND());
		this->OnWndCreated();
	}

	LRESULT WindowImpl::OnNcHitTest(WPARAM wParam, LPARAM lParam)
	{
		POINT pt;
		pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
		::ScreenToClient(*this, &pt);

		RECT rcClient;
		::GetClientRect(*this, &rcClient);

		if (!::IsZoomed(*this))
		{
			RECT rcSizeBox = _wc_.GetDragBorderSize();
			if (pt.y < rcClient.top + rcSizeBox.top)
			{
				if (pt.x < rcClient.left + rcSizeBox.left)
					return HTTOPLEFT;
				if (pt.x > rcClient.right - rcSizeBox.right)
					return HTTOPRIGHT;
				return HTTOP;
			}
			else if (pt.y > rcClient.bottom - rcSizeBox.bottom)
			{
				if (pt.x < rcClient.left + rcSizeBox.left)
					return HTBOTTOMLEFT;
				if (pt.x > rcClient.right - rcSizeBox.right)
					return HTBOTTOMRIGHT;
				return HTBOTTOM;
			}

			if (pt.x < rcClient.left + rcSizeBox.left)
				return HTLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right)
				return HTRIGHT;
		}

		RECT rcCaption = _wc_.GetCaption();
		if (pt.x >= rcClient.left + rcCaption.left
			&& pt.x < rcClient.right - rcCaption.right
			&& pt.y >= rcCaption.top
			&& pt.y < rcCaption.bottom)
		{
			return HTCAPTION;
			/*CControlUI* pControl = static_cast<CControlUI*>(FindControl(pt));
			if (pControl != NULL && !pControl->IsClientArea())
			{
				// 如果是活动控件，需要返回HTCLIENT以响应鼠标事件
				// 如果不是，则返回HTCAPTION处理标题栏拖动
				return HTCAPTION;
			}*/
		}

		return HTCLIENT;
	}

	void WindowImpl::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam)
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		MONITORINFO oMonitor = {};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTONEAREST), &oMonitor);
		Rect rcWork = oMonitor.rcWork;
		Rect rcMonitor = oMonitor.rcMonitor;
		rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

		// 计算最大化时，正确的原点坐标
		lpMMI->ptMaxPosition.x = rcWork.left;
		lpMMI->ptMaxPosition.y = rcWork.top;

		lpMMI->ptMaxTrackSize.x = rcWork.GetWidth();
		lpMMI->ptMaxTrackSize.y = rcWork.GetHeight();

		// TODO 使用窗口属性控制最小窗口尺寸
		lpMMI->ptMinTrackSize.x = _wc_.GetMinSize().cx;
		lpMMI->ptMinTrackSize.y = _wc_.GetMinSize().cy;
	}

	void WindowImpl::OnClose(WPARAM wParam, LPARAM lParam)
	{
		::SetFocus(nullptr);
		HWND hwndParent = GetWindowOwner(*this);
		if (hwndParent != nullptr)
			::SetFocus(hwndParent);
		this->OnWndClose();
	}

	void WindowImpl::OnDestory(WPARAM wParam, LPARAM lParam)
	{
		::ReleaseDC(*this, hPaintDC_);
		hPaintDC_ = nullptr;
		this->OnWndDestory();
	}

	void WindowImpl::OnNcCalcSize(WPARAM wParam, LPARAM lParam)
	{
		LPRECT pRect = nullptr;

		if (wParam == TRUE)
		{
			LPNCCALCSIZE_PARAMS pParam = (LPNCCALCSIZE_PARAMS)lParam;
			pRect = &pParam->rgrc[0];
		}
		else
		{
			pRect = (LPRECT)lParam;
		}

		if (::IsZoomed(*this))
		{	
			// 最大化时，计算当前显示器最适合宽高度
			// Win7屏幕扩展模式不会超过边界
			MONITORINFO oMonitor = {};
			oMonitor.cbSize = sizeof(oMonitor);
			::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTONEAREST), &oMonitor);
			Rect rcWork = oMonitor.rcWork;
			Rect rcMonitor = oMonitor.rcMonitor;
			rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

			pRect->right = pRect->left + rcWork.GetWidth();
			pRect->bottom = pRect->top + rcWork.GetHeight();
		}
	}

	void WindowImpl::OnPaint(WPARAM wParam, LPARAM lParam)
	{}

	void WindowImpl::OnSize(WPARAM param, LPARAM lParam)
	{
		Size round = _wc_.GetRoundCorner();
		if (!::IsIconic(*this) && (round.cx != 0 || round.cy != 0)) 
		{
			Rect rcWnd;
			::GetClientRect(*this, &rcWnd);
			rcWnd.Offset(-rcWnd.left, -rcWnd.top);
			rcWnd.right++; rcWnd.bottom++;
			HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, round.cx, round.cy);
			::SetWindowRgn(*this, hRgn, TRUE);
			::DeleteObject(hRgn);
		}
	}

	LRESULT WindowImpl::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (!::IsWindow(*this))
		{
			return false;
		}

		bool bHandled = false;
		LRESULT lRes = this->HandleMessage(uMsg, wParam, lParam, bHandled);
		if (bHandled == true)
		{
			return lRes;
		}
		lRes = this->HandleCustomMessage(uMsg, wParam, lParam, bHandled);
		if (bHandled == true)
		{
			return lRes;
		}

		return __super::WindowProc(uMsg, wParam, lParam);
	}

	bool WindowImpl::PreHandlerMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return false;
	}

	LRESULT WindowImpl::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
	{
		bHandled = false;
		return 0;
	}

	LRESULT WindowImpl::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
	{
		LRESULT lRes = S_OK;
		switch (uMsg)
		{
			case WM_CREATE:
			{
				OnCreate(wParam, lParam);
				bHandled = true;
				break;
			}
			case WM_CLOSE:
			{
				OnClose(wParam, lParam);
				break;
			}
			case WM_DESTROY:
			{
				OnDestory(wParam, lParam);
				lRes = S_FALSE;
				break;
			}
			case WM_NCACTIVATE:
			{
				bHandled = true;
				if (wParam == FALSE)
				{
					lRes = S_FALSE;
				}
				break;
			}
			case WM_NCCALCSIZE:
			{
				OnNcCalcSize(wParam, lParam);
				bHandled = true;
				if (::IsZoomed(*this))
				{
					return WVR_REDRAW;
				}
				break;
			}
			case WM_NCPAINT:
			{
				bHandled = false;
				break;
			}
			case WM_PAINT:
			{
				OnPaint(wParam, lParam);
				bHandled = true;
				break;
			}
			case WM_ERASEBKGND:
			{
				bHandled = true;
				lRes = S_FALSE;
				break;
			}
			case WM_NCHITTEST:	
			{
				bHandled = true;
				return OnNcHitTest(wParam, lParam);
				break;
			}
			case WM_GETMINMAXINFO:	
			{
				OnGetMinMaxInfo(wParam, lParam);
				bHandled = true;
				break;
			}
			case WM_SIZE:			
			{
				OnSize(wParam, lParam);
				OnWndSize();
				bHandled = true;
				break;
			}
			case WM_TIMER:
				break;
			case WM_SETCURSOR:
			{
				if (LOWORD(lParam) != HTCLIENT)
					break;
				if (_wc_.IsCapture())
				{
					bHandled = true;
					return TRUE;
				}
				// TODO：向控件发送事件
				bHandled = true;
				break;
			}
			case WM_CHAR:	
				OnChar(wParam);
				break;
			case WM_SYSCOMMAND:		
				if (wParam == SC_CLOSE)
				{
					SendMessage(WM_CLOSE);
				}
				OnSysCommand(wParam);
				bHandled = true;
				break;
			case WM_KEYUP:
				// TODO：向控件发送事件
				bHandled = true;
				break;
			case WM_KEYDOWN:
				OnKeyDown(wParam);
				bHandled = true;
				break;
			case WM_LBUTTONUP:	
				// TODO:向控件发送事件
				bHandled = true;
				break;
			case WM_LBUTTONDOWN:
				// TODO:向控件发送事件
				bHandled = true;
				break;
			case WM_LBUTTONDBLCLK:
				// TODO:向控件发送事件
				bHandled = true;
				break;
			case WM_RBUTTONDOWN:
				// TODO:向控件发送事件
				bHandled = true;
				break;
			case  WM_RBUTTONUP:
				// TODO:向控件发送事件
				bHandled = true;
				break;
			case WM_RBUTTONDBLCLK:
				// TODO:向控件发送事件
				bHandled = true;
				break;
			case WM_MOUSEWHEEL:
				// TODO:向控件发送事件
				bHandled = true;
				break;
			case WM_MOUSEMOVE:	
				// TODO:向控件发送事件
				bHandled = true;
				break;
			case WM_MOUSEHOVER:	
				// TODO:向控件发送事件
				bHandled = true;
				break;
			case WM_MOUSELEAVE:
				bHandled = true;
				break;
			default:				
				bHandled = false; 
				break;
		}

		return lRes;
	}

	// 窗口关闭操作
	void WindowImpl::OnWndClose()
	{}

	// 窗口创建完成，这里只能做FindControl操作
	void WindowImpl::OnWndCreated()
	{}

	// 窗口销毁
	void WindowImpl::OnWndDestory()
	{}

	// 窗口尺寸改变消息
	void WindowImpl::OnWndSize()
	{
		// TODO：在这里给控件发送大小改变的消息
	}

	// 按下字符键消息
	void WindowImpl::OnChar(WPARAM code)
	{}

	// 按键消息
	void WindowImpl::OnKeyDown(WPARAM code)
	{}

	void WindowImpl::OnSysCommand(WPARAM code)
	{}

	void WindowImpl::Notify(TNotify& notify)
	{}
}