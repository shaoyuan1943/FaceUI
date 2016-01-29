#pragma once
#ifndef _WINDOWCONTROLEVENT_H_
#define _WINDOWCONTROLEVENT_H_

namespace Face
{
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