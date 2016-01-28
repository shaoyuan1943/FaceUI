
#ifndef _WINDOWMANAGER_H_
#define _WINDOWMANAGER_H_

#pragma once

namespace Face
{
	class WndConfig;
	class MessageListener;
	class WindowImpl;

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

		void ShowWindow(LPCTSTR wndClassName, bool bShow = true, bool bTakeFocus = true);
		fuint ShowModal(HWND hParent, LPCTSTR wndClassName);
		void CloseWindow(LPCTSTR wndClassName, fuint ret = IDOK);

		void OnWndFinalMessage(LPCTSTR wndClassName);
	private:
		typedef std::list<ITranslateAccelerator*> MsgAcceleratorList;
		typedef std::unordered_map<std::wstring, WndConfig*> WndsConfigMap;

		WndsConfigMap *wndsConfigMap_;
		MsgAcceleratorList *acceleratorList_;

	};
}

#endif //_WINDOWMANAGER_H_