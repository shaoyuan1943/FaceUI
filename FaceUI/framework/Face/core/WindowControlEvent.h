#pragma once
#ifndef _WINDOWCONTROLEVENT_H_
#define _WINDOWCONTROLEVENT_H_

namespace Face
{
	/*
		这里是窗口控件处理消息和事件的地方
	*/
	class FACE_API WindowControlEvent : public NotCopyable
	{
	public:
		WindowControlEvent();
		virtual ~WindowControlEvent();

		virtual void OnWindowInit();
		virtual void OnButtonClicked(TNotify& notify);
		virtual void Notify(TNotify& notify);
	};
}
#endif //_WINDOWCONTROLEVENT_H_