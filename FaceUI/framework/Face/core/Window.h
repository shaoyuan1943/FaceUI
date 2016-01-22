#pragma once
#ifndef _WINDOW_H_
#define _WINDOW_H_

namespace Face
{
	class FACE_API Window
	{
	public:
		Window();
		virtual ~Window();

	public:
		HWND GetHWND() const;
		operator HWND() const;

		bool RegisterWndClass();
		
		bool SuperClass();

		void SetWndClassName(WString wndClassName);
		WString& GetWndClassName();

		void SetSuperClassName(WString superClassName);
		WString& GetSuperClassName();

		void SetWndClassStyle(fuint style);
		fuint GetWndClassStyle();

		HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc);
		HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT);

		void ShowWindow(bool bShow = true, bool bTakeFocus = true);
		fuint ShowModal();
		void Close(fuint ret = IDOK);
		void CenterWnd();

		void SetIcon(fuint res);

		void FullScreen();
		void RestoreFullScreen();

		LRESULT SendMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
		LRESULT PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
	protected:
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual void OnFinalMessage(HWND hWnd);

		static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	private:
		WString wndClassName_{ L"" };
		WString superClassName_{ L"" };
		fuint classStyle_{ 0 };
		HWND hWnd_{ nullptr };
		WNDPROC oldWndProc_;
		FaceRect restoreFullRect_;
	};
}
#endif