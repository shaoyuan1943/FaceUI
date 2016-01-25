
#ifndef _WINDOWMANAGER_H_
#define _WINDOWMANAGER_H_

#pragma once

namespace Face
{
	class WndConfig;
	class MessageListener;
	class WindowImpl;
	class FACE_API WndsMgr : public Singleton<WndsMgr>
	{
	public:
		virtual void Init(); 
		virtual void Destory();

		void AddWndConfig(LPCTSTR wndClassName, WndConfig* _pWo);
		WndConfig* GetWndConfig(LPCTSTR wndClassName);
		WndConfig* GetMainWndConfig();

		MessageListener* GetMessageListener(LPCTSTR wndClassName);

		void ShowWindow(LPCTSTR wndClassName, MessageListener *listener, bool bShow = true, bool bTakeFocus = true);
		fuint ShowModal(HWND hParent, LPCTSTR wndClassName, MessageListener *listener);
		void CloseWindow(fuint ret = IDOK);

		void OnWndFinalMessage(LPCTSTR wndClassName);
	private:
		typedef std::unordered_map<std::wstring, WndConfig*> WndsConfigMap;
		typedef std::unordered_map<std::wstring, MessageListener*> WindowsMessageListenersMap;
		WndsConfigMap *wndsConfigMap_;
		WindowsMessageListenersMap *windowsListenerMap_;

	};
}

#endif //_WINDOWMANAGER_H_