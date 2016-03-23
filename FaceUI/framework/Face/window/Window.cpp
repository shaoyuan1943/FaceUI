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

	const WString& Window::GetWndClassName()
	{
		return wndClassName_;
	}

	bool Window::RegisterWndClass(LPCTSTR className, fuint style)
	{
		WNDCLASS wc = { 0 };
		wc.style = style;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hIcon = nullptr;
		wc.lpfnWndProc = Window::__WndProc;
		wc.hInstance = App::getInstance()->GetAppInstance();
		wc.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = className;
		ATOM ret = ::RegisterClass(&wc);
		CHECK_ERROR(ret != 0 || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS, L"Register WNDCLASS failed");
		return ret != 0 || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
	}

	bool Window::SuperClass(LPCTSTR superClassName, LPCTSTR className)
	{
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(WNDCLASSEX);
		if (!::GetClassInfoEx(nullptr, superClassName, &wc))
		{
			if (!::GetClassInfoEx(App::getInstance()->GetAppInstance(), superClassName, &wc))
			{
				CHECK_ERROR(0, L"Unable to locate window class");
				return false;
			}
		}
		oldWndProc_ = wc.lpfnWndProc;
		wc.lpfnWndProc = Window::__ControlProc;
		wc.hInstance = App::getInstance()->GetAppInstance();
		wc.lpszClassName = className;
		ATOM ret = ::RegisterClassEx(&wc); 
		CHECK_ERROR(ret != 0 || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS, L"Super class Failed");
		return ret != 0 || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
	}

	HWND Window::Create(HWND hwndParent, LPCTSTR className, LPCTSTR pstrName, LPCTSTR superClassName/* = L"" */, DWORD dwStyle/* = UI_WNDSTYLE_FRAME */, DWORD dwExStyle/* = UI_WNDSTYLE_EX_FRAME */, fuint classStyle/* = UI_CLASSSTYLE_FRAME */)
	{
		CHECK_ERROR(className || className != L"", L"Create window failed.");
		CHECK_ERROR(pstrName || pstrName != L"", L"Create window failed.");
		if (!SuperClass(superClassName, className))
		{
			return nullptr;
		}

		if (!RegisterWndClass(className, classStyle))
		{
			return nullptr;
		}

		hWnd_ = ::CreateWindowEx(dwExStyle, className, pstrName, dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwndParent, nullptr, App::getInstance()->GetAppInstance(), this);
		CHECK_ERROR(hWnd_, L"Create window failed");
		wndClassName_ = className;
		return hWnd_;
	}

	LRESULT Window::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return ::CallWindowProc(oldWndProc_, hWnd_, uMsg, wParam, lParam);
	}

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
				return lRes;
			}
		}

		if (pThis != nullptr)
		{
			return pThis->WindowProc(uMsg, wParam, lParam);
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
				return lRes;
			}
		}
		if (pThis != NULL)
		{
			return pThis->WindowProc(uMsg, wParam, lParam);
		}
		else {
			return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
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
}