#pragma once
#ifndef _WINDOWIMPL_H_
#define _WINDOWIMPL_H_

namespace Face
{
	class MessageListener;
	class FACE_API WindowImpl : public Face::Window
	{
	public:
		WindowImpl();
		virtual ~WindowImpl();

		virtual LRESULT OnCreate(WPARAM wParam, LPARAM lParam, BOOL& handled);
		virtual LRESULT OnNcHitTest(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSysCommand(WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual void OnFinalMessage(HWND hWnd);
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		MessageListener *listener_{ nullptr };
	};
}
#endif