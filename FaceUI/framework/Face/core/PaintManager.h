#pragma once
#ifndef _PAINTMANAGER_H_
#define _PAINTMANAGER_H_

namespace Face
{
	class FACE_API PaintMgr : public NotCopyable
	{
	public:
		PaintMgr();
		~PaintMgr();

		void OnWndCreated(HWND hwnd);
	public:
		bool PreHandlerMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		bool MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);
	private:
		HWND hPaintWnd_{ nullptr };
		HDC hPaintDC_{ nullptr };
	};
}
#endif //_PAINTMANAGER_H_