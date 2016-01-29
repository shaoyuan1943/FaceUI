
#ifndef _WINDOWMANAGER_H_
#define _WINDOWMANAGER_H_

#pragma once

namespace Face
{
	class Control;
	class WndConfig;
	class WindowImpl;
	class MessageListener;
	class WindowControlEvent;

	class FACE_API ITranslateAccelerator : public NotCopyable
	{
	public:
		virtual LRESULT TranslateAccelerator(MSG *pMsg) = 0;
	};

	class FACE_API WndsMgr : public Singleton<WndsMgr>
	{
	public:
		virtual void Init(); 
		virtual void Destory();

		void AddWndConfig(LPCTSTR wndClassName, WndConfig* _pWo);
		WndConfig* GetWndConfig(LPCTSTR wndClassName);
		WndConfig* GetMainWndConfig();
		void MessageLoop();

		void RegisterTranslateAccelerator(ITranslateAccelerator *acclerator);
		void RemoveTranslateAccelerator(ITranslateAccelerator *acclerator);
		bool TranslateMessage(const LPMSG pMsg);
		void TranslateAccelerator(MSG *msg);

		bool RegisterWndEvent(HWND hwnd, WindowControlEvent *event);
		bool RemoveWndEvent(HWND hwnd);
		bool RemoveWndEvent(WindowControlEvent *event);

		void NotifyHandler(HWND hwnd, Control* notifyControl, int msg, WPARAM wParam = 0, LPARAM lParam = 0);

		void ShowWindow(LPCTSTR wndClassName, bool bShow = true, bool bTakeFocus = true);
		fuint ShowModal(HWND hParent, LPCTSTR wndClassName);
		void CloseWindow(LPCTSTR wndClassName, fuint ret = IDOK);

		void OnWndFinalMessage(LPCTSTR wndClassName);
	private:
		WindowControlEvent* GetWndEvent(HWND hwnd);
	private:
		typedef std::list<ITranslateAccelerator*> MsgAcceleratorList;
		typedef std::unordered_map<std::wstring, WndConfig*> WndsConfigMap;
		typedef std::unordered_map<HWND, WindowControlEvent*> WndsEventMap;
		WndsConfigMap *wndsConfigMap_;
		MsgAcceleratorList *acceleratorList_;
		WndsEventMap *eventMap_;

	};
}

#endif //_WINDOWMANAGER_H_