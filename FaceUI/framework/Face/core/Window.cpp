#include "stdafx.h"

namespace Face
{
	Window::Window()
	{}

	Window::~Window()
	{}

	HWND Window::GetHWND() const
	{
		return hWnd_;
	}

	Window::operator HWND()const
	{
		return hWnd_;
	}

	void Window::SetWndClassName(WString wndClassName)
	{
		CHECK_ERROR(wndClassName.Length(), L"Window class name not allowed empty");
		if (wndClassName != wndClassName_)
		{
			wndClassName_ = wndClassName;
		}
	}
	
	WString& Window::GetWndClassName()
	{
		return wndClassName_;
	}

	void Window::SetSuperClassName(WString superClassName)
	{
		if (superClassName.Length() > 0 && superClassName != superClassName_)
		{
			superClassName_ = superClassName;
		}
	}

	WString& Window::GetSuperClassName()
	{
		return superClassName_;
	}

	void Window::SetWndClassStyle(fuint style)
	{
		if (style != classStyle_)
		{
			classStyle_ = style;
		}
	}

	fuint Window::GetWndClassStyle()
	{
		return classStyle_;
	}

	bool Window::RegisterWndClass()
	{
		WNDCLASS wc = { 0 };
		wc.style = GetWndClassStyle();
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hIcon = nullptr;
		wc.lpfnWndProc = Window::__WndProc;
		wc.hInstance = FaceApp::getInstance()->GetAppInstance();
		wc.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = GetWndClassName().Buffer();
		ATOM ret = ::RegisterClass(&wc);
		CHECK_ERROR(ret != 0 || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS, L"Register WNDCLASS failed");
		return ret != 0 || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
	}

	bool Window::SuperClass()
	{
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(WNDCLASSEX);
		if (!::GetClassInfoEx(nullptr, GetSuperClassName().Buffer(), &wc))
		{
			if (!::GetClassInfoEx(FaceApp::getInstance()->GetAppInstance(), GetSuperClassName().Buffer(), &wc))
			{
				CHECK_ERROR(0, L"Unable to locate window class");
				return false;
			}
		}
		oldWndProc_ = wc.lpfnWndProc;
		wc.lpfnWndProc = Window::__ControlProc;
		wc.hInstance = FaceApp::getInstance()->GetAppInstance();
		wc.lpszClassName = GetWndClassName().Buffer();
		ATOM ret = ::RegisterClassEx(&wc);
		CHECK_ERROR(ret != 0 || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS, L"Super class Failed");
		return ret != 0 || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
	}

	HWND Window::Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x /* = CW_USEDEFAULT */, int y /* = CW_USEDEFAULT */, int cx /* = CW_USEDEFAULT */, int cy /* = CW_USEDEFAULT */)
	{
		if (GetSuperClassName().Length() > 0 && !SuperClass())
		{
			return nullptr;
		}

		if (GetSuperClassName().Length() <= 0 && !RegisterWndClass())
		{
			return nullptr;
		}

		hWnd_ = ::CreateWindowEx(dwExStyle, GetWndClassName().Buffer(), pstrName, dwStyle, x, y, cx, cy, hwndParent, nullptr, FaceApp::getInstance()->GetAppInstance(), this);
		CHECK_ERROR(hWnd_, L"Create window failed");
		return hWnd_;
	}

	HWND Window::Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc)
	{
		return Create(hwndParent, pstrName, dwStyle, dwExStyle, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
	}

	LRESULT Window::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return ::CallWindowProc(oldWndProc_, hWnd_, uMsg, wParam, lParam);
	}

	void Window::OnFinalMessage(HWND hWnd)
	{}

	LRESULT CALLBACK Window::__WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Window *pThis = nullptr;
		if (uMsg == WM_NCCREATE)
		{
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			pThis = static_cast<Window*>(lpcs->lpCreateParams);
			pThis->hWnd_ = hWnd;
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(pThis));
		}
		else
		{
			pThis = reinterpret_cast<Window*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
			if (uMsg == WM_NCDESTROY && pThis != nullptr)
			{
				LRESULT lRes = ::CallWindowProc(pThis->oldWndProc_, hWnd, uMsg, wParam, lParam);
				::SetWindowLongPtr(pThis->hWnd_, GWLP_USERDATA, 0L);
				pThis->hWnd_ = nullptr;
				pThis->OnFinalMessage(hWnd);	//OnFinalMessage做最后处理
				return lRes;
			}
		}

		if (pThis != nullptr)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else
		{
			return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}

	LRESULT CALLBACK Window::__ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Window* pThis = nullptr;
		if (uMsg == WM_NCCREATE)
		{
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			pThis = static_cast<Window*>(lpcs->lpCreateParams);
			::SetProp(hWnd, L"WndX", (HANDLE)pThis);
			pThis->hWnd_ = hWnd;
		}
		else
		{
			pThis = reinterpret_cast<Window*>(::GetProp(hWnd, L"WndX"));
			if (uMsg == WM_NCDESTROY && pThis != nullptr)
			{
				LRESULT lRes = ::CallWindowProc(pThis->oldWndProc_, hWnd, uMsg, wParam, lParam);
				::SetProp(hWnd, L"WndX", nullptr);
				pThis->hWnd_ = NULL;
				pThis->OnFinalMessage(hWnd);
				return lRes;
			}
		}
		if (pThis != NULL)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else {
			return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}

	void Window::ShowWindow(bool bShow/* = true */, bool bTakeFocus/* = true*/)
	{
		CHECK_ERROR(::IsWindow(hWnd_), L"Not window");
		::ShowWindow(hWnd_, bShow ? (bTakeFocus ? SW_SHOWNORMAL : SW_SHOWNOACTIVATE) : SW_HIDE);
	}

	fuint Window::ShowModal()
	{
		CHECK_ERROR(::IsWindow(hWnd_), L"Not window");
		fuint ret = 0;
		HWND hWndParent = ::GetWindowOwner(hWnd_);
		::ShowWindow(hWnd_, SW_SHOWNORMAL);	//将窗口显示出来
		::EnableWindow(hWndParent, FALSE);	//然后将父窗口设置不可用
		MSG msg = { 0 };
		//消息循环，处理显示出来的窗口所产生的消息
		while (::IsWindow(hWnd_) && ::GetMessage(&msg, NULL, 0, 0))
		{
			if (msg.message == WM_CLOSE && msg.hwnd == hWnd_)
			{
				ret = msg.wParam;
				::EnableWindow(hWndParent, TRUE);
				::SetFocus(hWndParent);
			}
			// 消息流转
			/*if (!CPaintManagerUI::TranslateMessage(&msg))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}*/

			if (msg.message == WM_QUIT)	//一旦在队列中收到退出的消息，中断消息循环，处理退出
				break;
		}
		::EnableWindow(hWndParent, TRUE);	//说明显示的窗口要退出，然后将父窗口设置为可用
		::SetFocus(hWndParent);	//设置父窗口焦点
								//退出
		if (msg.message == WM_QUIT)
			::PostQuitMessage(msg.wParam);
		return ret;
	}

	void Window::Close(fuint ret /* = IDOK */)
	{
		CHECK_ERROR(::IsWindow(hWnd_), L"Not window");
		PostMessage(WM_CLOSE, (WPARAM)ret, 0L);
	}

	void Window::CenterWnd()
	{
		CHECK_ERROR(::IsWindow(hWnd_), L"Not window");
		CHECK_ERROR(GetWindowStyle(hWnd_) & WS_CHILD == 0, L"It's be child");

		RECT rcDlg = { 0 };
		::GetWindowRect(hWnd_, &rcDlg);
		RECT rcArea = { 0 };
		RECT rcCenter = { 0 };
		HWND hWnd = *this;
		HWND hWndParent = ::GetParent(hWnd_);
		HWND hWndCenter = ::GetWindowOwner(hWnd_);
		if (hWndCenter != nullptr)
			hWnd = hWndCenter;

		// 处理多显示器模式下屏幕居中
		MONITORINFO oMonitor = {};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), &oMonitor);
		rcArea = oMonitor.rcWork;

		if (hWndCenter == nullptr)
			rcCenter = rcArea;
		else
			::GetWindowRect(hWndCenter, &rcCenter);

		int DlgWidth = rcDlg.right - rcDlg.left;
		int DlgHeight = rcDlg.bottom - rcDlg.top;

		// Find dialog's upper left based on rcCenter
		int xLeft = (rcCenter.left + rcCenter.right) / 2 - DlgWidth / 2;
		int yTop = (rcCenter.top + rcCenter.bottom) / 2 - DlgHeight / 2;

		// The dialog is outside the screen, move it inside
		if (xLeft < rcArea.left)
			xLeft = rcArea.left;
		else if (xLeft + DlgWidth > rcArea.right)
			xLeft = rcArea.right - DlgWidth;

		if (yTop < rcArea.top) 
			yTop = rcArea.top;
		else if (yTop + DlgHeight > rcArea.bottom)
			yTop = rcArea.bottom - DlgHeight;

		::SetWindowPos(hWnd_, nullptr, xLeft, yTop, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	LRESULT Window::SendMessage(UINT uMsg, WPARAM wParam/* = 0 */, LPARAM lParam/* = 0L */)
	{
		CHECK_ERROR(::IsWindow(hWnd_), L"Not window");
		return ::SendMessage(hWnd_, uMsg, wParam, lParam);
	}

	LRESULT Window::PostMessage(UINT uMsg, WPARAM wParam/* = 0 */, LPARAM lParam/* = 0L */)
	{
		CHECK_ERROR(::IsWindow(hWnd_), L"Not window");
		return ::PostMessage(hWnd_, uMsg, wParam, lParam);
	}

	void Window::SetIcon(fuint res)
	{
		HICON hIcon = (HICON)::LoadImage(FaceApp::getInstance()->GetAppInstance(), MAKEINTRESOURCE(res), IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);

		CHECK_ERROR(hIcon, L"Icon handler is null");

		::SendMessage(hWnd_, WM_SETICON, (WPARAM)TRUE, (LPARAM)hIcon);
		hIcon = (HICON)::LoadImage(FaceApp::getInstance()->GetAppInstance(), MAKEINTRESOURCE(res), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);

		CHECK_ERROR(hIcon, L"Icon handler is null");

		::SendMessage(hWnd_, WM_SETICON, (WPARAM)FALSE, (LPARAM)hIcon);
	}

	void Window::FullScreen()
	{
		::GetClientRect(hWnd_, &restoreFullRect_);
		FacePoint point;
		::ClientToScreen(hWnd_, &point);
		restoreFullRect_.left = point.x;
		restoreFullRect_.top = point.y;
		restoreFullRect_.right += point.x;
		restoreFullRect_.bottom += point.y;
		MONITORINFO oMonitor = {};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTONEAREST), &oMonitor);
		FaceRect rcWork = oMonitor.rcWork;

		::SetWindowPos(hWnd_, nullptr, rcWork.left, rcWork.top, rcWork.GetWidth(), rcWork.GetHeight(), SWP_SHOWWINDOW | SWP_NOZORDER);
	}

	void Window::RestoreFullScreen()
	{
		::SetWindowPos(hWnd_, NULL, restoreFullRect_.left, restoreFullRect_.top, restoreFullRect_.GetWidth(), restoreFullRect_.GetHeight(), SWP_SHOWWINDOW | SWP_NOZORDER);
	}
}