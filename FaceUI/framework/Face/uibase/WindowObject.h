
#ifndef _WINDOWOBJECT_H_
#define _WINDOWOBJECT_H_

#pragma once

namespace Face
{
	class FaceWindowImpl;
	class FACE_API FaceWindowObject : public Face::FaceObject
	{
	public:
		FaceWindowObject();
		virtual ~FaceWindowObject();

		WString wndClassName;
		WString wndName;
		WString wndFile;
		WString wndEventClass;
		bool	isMainWnd;
		FaceWindowImpl *wnd{ nullptr };
		fuint style{ 0 };
		fuint exStyle{ 0 };
	};
}
#endif // _WINDOWOBJECT_H_