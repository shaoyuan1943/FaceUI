
#ifndef _WINDOWMANAGER_H_
#define _WINDOWMANAGER_H_

#pragma once

namespace Face
{
	class FaceWindowObject;
	class FaceMessageListener;
	class FaceWindowImpl;
	class FACE_API FaceWndsMgr : public FaceSingleton<FaceWndsMgr>
	{
	public:
		virtual void Init();
		virtual void Destory();

		void AddWindow(const wchar_t* wndClassName, FaceWindowObject* _pWo);
		FaceWindowObject* GetWindowObject(const wchar_t* wndClassName);
		FaceWindowObject* GetMainWindowObject();

		void RegisterMessageListener(const wchar_t* wndClassName, FaceMessageListener *listener);
		FaceMessageListener* GetMessageListener(const wchar_t *wndClassName);

		void ShowWindow(const wchar_t *wndClassName, bool bShow = true, bool bTakeFocus = true);
		fuint ShowModal();
		void CloseWindow(fuint ret = IDOK);
	private:
		typedef std::unordered_map<std::wstring, FaceWindowObject*> WindowsObjectMap;
		typedef std::unordered_map<std::wstring, FaceMessageListener*> WindowsMessageListenersMap;
		WindowsObjectMap *windowsObejctMap_;
		WindowsMessageListenersMap *windowsListenerMap_;

	};
}

#endif //_WINDOWMANAGER_H_