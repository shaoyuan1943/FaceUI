#pragma once
#ifndef _WINDOW_H_
#define _WINDOW_H_

namespace Face
{
	class FACE_API Window
	{
		friend class WndsMgr;
	public:
		Window();
		virtual ~Window();
	public:
		HWND GetHWND() const;
		operator HWND() const;

		SYNTHESIZE_PRI_CONST_REF_GET(WString, wndClassName_, WndClassName);

		void ShowWindow(bool bShow = true, bool bTakeFocus = true);
		fuint ShowModal();
		void Close(fuint ret = IDOK);
		void Center();

		void SetIcon(fuint res);

		void FullScreen();
		void RestoreFullScreen();

		LRESULT SendMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
		LRESULT PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);

	private:
		bool RegisterWndClass(LPCTSTR className, fuint style);
		bool SuperClass(LPCTSTR superClassName, LPCTSTR className);

	protected:
		HWND Create(HWND hwndParent, LPCTSTR className, LPCTSTR pstrName, LPCTSTR superClassName = L"", DWORD dwStyle = UI_WNDSTYLE_FRAME, DWORD dwExStyle = UI_WNDSTYLE_EX_FRAME, fuint classStyle = UI_CLASSSTYLE_FRAME);

		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual void OnFinalMessage(HWND hWnd);

		static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	private:
		HWND hWnd_{ nullptr };
		WNDPROC oldWndProc_;
		Rect restoreFullRect_;
	};
}
#endif