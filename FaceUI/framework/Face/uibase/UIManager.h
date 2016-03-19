
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
		virtual LRESULT TranslateAccelerator(const LPMSG pMsg) = 0;
	};

	/*
		FaceUI中窗口和控件的管理类
		消息转发类
		提供了加速键消息处理列表、窗口事件列表、以及第三方控件创建列表
	*/
	class FACE_API UIMgr : public Singleton<UIMgr>
	{
	public:
		template<typename T>
		class ControlFactory
		{
		public:
			ControlFactory(const WString& key)
			{
				UIMgr::getInstance()->regControlsMap_->emplace(key, []()->Control* {return new T; });
			}
		};

		typedef Control* (_cdecl *CONTROL_CREATER)();
		typedef std::list<ITranslateAccelerator*> MsgAcceleratorList;
		typedef std::map<WString, WndConfig*> WndsConfigMap;
		typedef std::map<HWND, WindowControlEvent*> WndsEventMap;
		typedef std::map<WString, std::function<Control*()> > ControlsMap;

		virtual void Init(); 
		virtual void Destory();

		Control* CreateControl(LPCTSTR lpszType);

		// 窗口相关
		void AddWndConfig(LPCTSTR wndClassName, WndConfig* _pWo);
		WndConfig* GetWndConfig(LPCTSTR wndClassName);
		WndConfig* GetMainWndConfig();
		void ShowWindow(LPCTSTR wndClassName, bool bShow = true, bool bTakeFocus = true);
		fuint ShowModal(HWND hParent, LPCTSTR wndClassName);
		void CloseWindow(LPCTSTR wndClassName, fuint ret = IDOK);

		// 消息相关
		void MessageLoop();
		bool TranslateMessage(const LPMSG pMsg);
		void TranslateAccelerator(const LPMSG pMsg);
		// 自定义加速键消息
		void RegisterTranslateAccelerator(ITranslateAccelerator *acclerator);
		void RemoveTranslateAccelerator(ITranslateAccelerator *acclerator);
		void RemoveAllTranslateAccelerator();

		void NotifyHandler(HWND hwnd, Control* notifyControl, NOTIFY msg, WPARAM wParam = 0, LPARAM lParam = 0);
	private:
		// 辅助函数
		WindowControlEvent* GetWndEvent(HWND hwnd);
	private:
		std::unique_ptr<WndsConfigMap>		wndsConfigMap_;
		std::unique_ptr<MsgAcceleratorList> acceleratorList_;
		std::unique_ptr<ControlsMap>		regControlsMap_;
	};
}

#define REGISTER_VALUE_NAME(T) reg_msg_##T##_
#define REGISTER_CREATER(T, key) Face::UIMgr::ControlFactory<T> REGISTER_VALUE_NAME(T)(key);

#endif //_WINDOWMANAGER_H_