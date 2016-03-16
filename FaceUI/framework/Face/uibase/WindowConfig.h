
#ifndef _WNDCONFIG_H_
#define _WNDCONFIG_H_

#pragma once

namespace Face
{
	class WindowImpl;
	class MessageListener;
	/*
		¥∞ø⁄ª˘¥°≈‰÷√¿‡
	*/
	class FACE_API WndConfig : public Face::NotCopyable
	{
		friend class UIMgr;
		friend class ParseResourceIndexFileDelegate;
	public:
		WndConfig();
		virtual ~WndConfig();

		SYNTHESIZE_PRI_CONST_REF_GET(WString, wndClassName_, WndClassName);
		SYNTHESIZE_PRI_CONST_REF_GET(WString, wndName_, WndName);
		SYNTHESIZE_PRI_CONST_REF_GET(WString, wndXmlFile_, WndXMLFile);

		inline WindowImpl* GetWndImpl() { return wnd_; };
	private:
		bool		isMainWnd_;
		fuint		style_{ 0 };
		fuint		exStyle_{ 0 };
		fuint		classStyle_{ 0 };
		WindowImpl	*wnd_{ nullptr };
	};
}
#endif // _WNDCONFIG_H_