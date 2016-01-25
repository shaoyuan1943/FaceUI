#pragma once
#ifndef _MESSAGELISTENER_H_
#define _MESSAGELISTENER_H_

namespace Face
{
	class WindowImpl;
	class FACE_API MessageListener
	{
	public:
		MessageListener();
		virtual ~MessageListener();

	public:
		virtual void OnFinalMessage(HWND hWnd);
		virtual LRESULT OnCreate(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnClose(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDestroy(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNcActivate(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNcCalcSize(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNcPaint(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNcHitTest(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseWheel(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSize(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnChar(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSysCommand(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnKeyDown(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnKillFocus(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSetFocus(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT HandleCustomMessage(WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	protected:
		WindowImpl *wndOwner_{ nullptr };
	};
}
#endif