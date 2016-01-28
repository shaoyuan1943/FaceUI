#pragma once
#ifndef _WINDOWIMPL_H_
#define _WINDOWIMPL_H_

namespace Face
{
	class WindowControl;
	class FACE_API WindowImpl : public Face::Window
	{
	public:
		WindowImpl();
		virtual ~WindowImpl();
		WindowControl* GetPaintMgr();

		// 对外接口
		virtual void OnFinalMessage(HWND hWnd);
		virtual void OnWndCreated();
		virtual void OnWndClose();
		virtual void OnWndDestory();
		virtual void OnWndSize();
		virtual void OnChar(WPARAM code);
		virtual void OnKeyDown(WPARAM code);
		virtual void OnSysCommand(WPARAM code);
		virtual bool PreHandlerMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		void OnCreate(WPARAM wParam, LPARAM lParam);
		LRESULT OnNcHitTest(WPARAM wParam, LPARAM lParam);
		void OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);
		void OnClose(WPARAM wParam, LPARAM lParam);
		void OnDestory(WPARAM wParam, LPARAM lParam);
		void OnNcCalcSize(WPARAM wParam, LPARAM lParam);
		void OnPaint(WPARAM wParam, LPARAM lParam);
		void OnSize(WPARAM param, LPARAM lParam);

		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	protected:
		virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	protected:
		WindowControl _wc_;
		HDC hPaintDC_{ nullptr };
	};
}
#endif