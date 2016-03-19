#pragma once
#ifndef _CONTROL_H_
#define _CONTROL_H_

namespace Face
{
	class WindowImpl;
	class WindowControl;
	/*
		控件基类，所有的控件需强制继承此类
	*/
	class FACE_API Control : public NotCopyable
	{
	public:
		Control();
		virtual ~Control();

		virtual WString GetClassName() { return L"Control"; };
		virtual LPVOID GetInterface(LPCTSTR pstrName);

		virtual void Invalidate();
		virtual void SetAttribute(LPCTSTR key, LPCTSTR value);

		SYNTHESIZE_PRI(WindowImpl*, wndImpl_, WindowImpl);
		SYNTHESIZE_PRI(Control*, parent_, Parent);
		SYNTHESIZE_PRI(bool, focused_, Focus);

		virtual void EventHandler(TEvent& event);
		/*
			内部事件转换成外部事件
		*/
	};
}
#endif //_CONTROL_H_