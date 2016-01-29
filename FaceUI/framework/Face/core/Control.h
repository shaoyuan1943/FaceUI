#pragma once
#ifndef _CONTROL_H_
#define _CONTROL_H_

namespace Face
{
	class WindowControl;
	class FACE_API Control : public NotCopyable
	{
	public:
		Control();
		virtual ~Control();

		void Invalidate();

		OBJECT_CREATE(Control);
		SYNTHESIZE_PRI(WindowControl*, wc_, WindowControl);
		SYNTHESIZE_PRI(Control*, parent_, Parent);
		SYNTHESIZE_PRI(bool, focused_, Focus);

		void EventHandler(TEvent& event);
		/*
			内部事件转换成外部事件
		*/
	};
}
#endif //_CONTROL_H_