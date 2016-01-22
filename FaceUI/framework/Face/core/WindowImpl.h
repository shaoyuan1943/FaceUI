#pragma once
#ifndef _WINDOWIMPL_H_
#define _WINDOWIMPL_H_

namespace Face
{
	class FaceMessageListener;
	class FACE_API FaceWindowImpl : public Face::Window
	{
	public:
		FaceWindowImpl();
		virtual ~FaceWindowImpl();

		virtual void OnFinalMessage(HWND hWnd);
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		FaceMessageListener *listener_{ nullptr };
	};
}
#endif