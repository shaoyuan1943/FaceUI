#pragma once
#ifndef _MESSAGELISTENER_H_
#define _MESSAGELISTENER_H_

namespace Face
{
	class WindowImpl;
	class FACE_API MessageListener : public Face::NotCopyable
	{
	public:
		MessageListener();
		virtual ~MessageListener();

		virtual void OnWndCreated();
		virtual void OnWndClose();
		virtual void OnWndDestory();
		virtual void OnWndSize();
		virtual void OnChar(WPARAM code);
		virtual void OnKeyDown(WPARAM code);
		virtual void OnSysCommand(WPARAM code);
	
		virtual void OnFinalMessage(HWND hWnd);
		virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	};
}
#endif