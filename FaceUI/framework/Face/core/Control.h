#pragma once
#ifndef _CONTROL_H_
#define _CONTROL_H_

namespace Face
{
	class FACE_API Control : public NotCopyable
	{
	public:
		Control();
		virtual ~Control();

		OBJECT_CREATE(Control);

		/*
			内部事件转换成外部事件
		*/
	};
}
#endif //_CONTROL_H_