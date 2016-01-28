#pragma once
#ifndef _PAINTMANAGER_H_
#define _PAINTMANAGER_H_

namespace Face
{
	/*
		window 类的分割，将Direct Window分割成传统窗口类和Window控件
		前者处理Window基本内容，后者处理与这个窗口相应的各种属性和消息。
	*/ 
	class FACE_API WindowControl : public NotCopyable
	{
	public:
		WindowControl();
		~WindowControl();

		void OnWndCreated(HWND hwnd);
		
		// 可拖动改变窗口大小的边距
		SYNTHESIZE_PRI_CONST_REF(Rect, dragBorderSize_, DragBorderSize);
		// 可拖动的标题栏大小的边距
		SYNTHESIZE_PRI_CONST_REF(Rect, caption_, Caption);
		// 窗口最大大小
		SYNTHESIZE_PRI_CONST_REF(Size, maxSize_, MaxSize);
		// 窗口最小大小
		SYNTHESIZE_PRI_CONST_REF(Size, minSize_, MinSize);
		// 窗口圆角大小
		SYNTHESIZE_PRI_CONST_REF(Size, roundCorner_, RoundCorner);

		void SetCapture();
		void ReleaseCapture();
		bool IsCapture();
	private:
		HWND hPaintWnd_{ nullptr };
		bool isCapture_{ false };

		// 事件
	};
}
#endif //_PAINTMANAGER_H_