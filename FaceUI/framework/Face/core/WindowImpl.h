#pragma once
#ifndef _WINDOWIMPL_H_
#define _WINDOWIMPL_H_

namespace Face
{
	class WindowControl;
	/*
		窗口类的实现，在FaceUI中，一个完整的窗口被拆分成Window，WindowImpl, WindowControl, WindowControlEvent
		Window：窗口基类，它提供了一个窗口最基本的功能和win32窗口接口
		WindowImpl：窗口实现类，它实现了FaceUI窗口，窗口绘制、windows消息
		WindowControl：在其他DirectUI库中，Window既是传统窗口又是Direct窗口，在FaceUI中被拆分开，Window，WindowImpl是
		传统的窗口，而WindowControl则是窗口控件，与窗口有关的Direct属性或者操作全部都在WindowControl中。
		WindowControlEvent：WindowControl（Window控件）的消息实体.
	*/
	class FACE_API WindowImpl : public Face::Window, Face::WindowControlEvent
	{
	public:
		WindowImpl();
		virtual ~WindowImpl();
		WindowControl* GetWndControl();
		// 控件事件处理，包括普通控件和windows控件
		virtual void Notify(TNotify& notify);
		virtual bool PreHandlerMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	private:
		LRESULT OnNcHitTest(WPARAM wParam, LPARAM lParam);
		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
		void OnCreate(WPARAM wParam, LPARAM lParam);
		void OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);
		void OnClose(WPARAM wParam, LPARAM lParam);
		void OnDestory(WPARAM wParam, LPARAM lParam);
		void OnNcCalcSize(WPARAM wParam, LPARAM lParam);
		void OnPaint(WPARAM wParam, LPARAM lParam);
		void OnSize(WPARAM param, LPARAM lParam);
	protected:
		virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

		// 这两个消息是从Window流下来的
		virtual void OnWndCreated();
		virtual void OnWndDestory();

		// 可以处理的消息
		virtual void OnWndClosed();
		virtual void OnWndSized();
		virtual void OnWndChar(WPARAM code);
		virtual void OnWndKeyDown(WPARAM code);
		virtual void OnWndSysCommand(WPARAM code);
	protected:
		WindowControl _wc_;
		HDC hPaintDC_{ nullptr };
		WString name;
	};
}
#endif