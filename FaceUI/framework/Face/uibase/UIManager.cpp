#include "stdafx.h"
#include "match.hpp"

namespace Face
{
	void UIMgr::Init()
	{
		wndsConfigMap_		= new WndsConfigMap;
		acceleratorList_	= new MsgAcceleratorList;
		eventMap_			= new WndsEventMap;
		regControlsMap_		= new ControlsMap;
	}

	void UIMgr::RegisterCustomControlsBuilder(ICustomBuilder *creater)
	{
		CHECK_ERROR(creater, L"");
		customBuilder_ = creater;
	}

	Control* UIMgr::CreateControl(LPCTSTR pszType)
	{
		CHECK_ERROR(pszType, L"");
		CHECK_ERROR(pszType != L"", L"");

		auto control = regControlsMap_->find(pszType);
		if (control != regControlsMap_->end())
		{
			return control->second();
		}

		return customBuilder_->CreateCustomControls(pszType);
	}

	void UIMgr::Destory()
	{
		// TODO: delete
		for (auto it = wndsConfigMap_->begin(); it != wndsConfigMap_->end(); it++)
		{
			auto wc = it->second;
			if (wc)
			{
				if (wc->wnd_)
				{
					SAFE_DELETE(wc->wnd_);
				}
			}

			SAFE_DELETE(wc);
		}
		wndsConfigMap_->clear();
		
		for (auto it = acceleratorList_->begin(); it != acceleratorList_->end(); it++)
		{
			SAFE_DELETE(*it);
		}
		acceleratorList_->clear();
	}

	void UIMgr::AddWndConfig(LPCTSTR wndClassName, WndConfig* _pWo)
	{
		CHECK_ERROR(wndClassName, L"");
		CHECK_ERROR(_pWo, L"");

		wndsConfigMap_->insert(std::make_pair(wndClassName, _pWo));
	}

	void UIMgr::OnWndFinalMessage(LPCTSTR wndClassName)
	{
		CHECK_ERROR(wndClassName, L"");
		CHECK_ERROR(wndClassName != L"", L"");

		auto wo = GetWndConfig(wndClassName);
		SAFE_DELETE(wo->wnd_);
	}

	WndConfig* UIMgr::GetWndConfig(LPCTSTR wndClassName)
	{
		CHECK_ERROR(wndClassName, L"");
		auto it = wndsConfigMap_->find(wndClassName);
		if (it != wndsConfigMap_->end())
		{
			return it->second;
		}

		return nullptr;
	}

	WndConfig* UIMgr::GetMainWndConfig()
	{
		for (auto it = wndsConfigMap_->begin(); it != wndsConfigMap_->end(); it++)
		{
			auto wo = it->second;
			if (wo->isMainWnd_)
			{
				return wo;
			}
		}

		return nullptr;
	}

	void UIMgr::ShowWindow(LPCTSTR wndClassName, bool bShow/* = true */, bool bTakeFocus/* = true */)
	{
		CHECK_ERROR(wndClassName, L"");
		CHECK_ERROR(wndClassName != L"", L"");

		WndConfig *config = nullptr;
		for (auto it = wndsConfigMap_->begin(); it != wndsConfigMap_->end(); it++)
		{
			config = it->second;
			if (wcscmp(config->wndClassName_.Buffer(), wndClassName) == 0)
			{
				break;
			}
		}

		if (config)
		{
			auto wndImpl = new WindowImpl;
			config->wnd_ = wndImpl;
			wndImpl->Create(nullptr, wndClassName, config->wndName_.Buffer(), L"", config->style_, config->exStyle_, config->classStyle_);
			wndImpl->ShowWindow();
		}
	}

	fuint UIMgr::ShowModal(HWND hParent, LPCTSTR wndClassName)
	{
		CHECK_ERROR(hParent, L"Create model window failed.");
		CHECK_ERROR(wndClassName || wndClassName != L"", L"Create model window failed.");
		WndConfig *config = nullptr;
		for (auto it = wndsConfigMap_->begin(); it != wndsConfigMap_->end(); it++)
		{
			config = it->second;
			if (wcscmp(config->wndClassName_.Buffer(), wndClassName) == 0)
			{
				break;
			}
		}

		if (config)
		{
			auto wndImpl = new WindowImpl;
			config->wnd_ = wndImpl;
			wndImpl->Create(hParent, wndClassName, config->wndName_.Buffer(), L"", config->style_, config->exStyle_, config->classStyle_);
			return wndImpl->ShowModal();
		}
		return IDCANCEL;
	}

	void UIMgr::CloseWindow(LPCTSTR wndClassName, fuint ret/* = IDOK */)
	{
		CHECK_ERROR(wndClassName || wndClassName != L"", L"Close window window failed.");
		for (auto it = wndsConfigMap_->begin(); it != wndsConfigMap_->end(); it++)
		{
			auto wc = it->second;
			if (wcscmp(wc->wndClassName_.Buffer(), wndClassName) == 0)
			{
				if (wc && wc->wnd_)
				{
					wc->wnd_->Close(ret);
					return;
				}
			}
		}
	}

	void UIMgr::MessageLoop()
	{
		MSG msg = { 0 };
		while (::GetMessage(&msg, NULL, 0, 0))
		{
			if (!UIMgr::getInstance()->TranslateMessage(&msg))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}
	}

	void UIMgr::RegisterTranslateAccelerator(ITranslateAccelerator *acclerator)
	{
		CHECK_ERROR(acclerator, L"TranslateAccelerator not be null.");
		acceleratorList_->push_back(acclerator);
	}

	void UIMgr::RemoveTranslateAccelerator(ITranslateAccelerator *acclerator)
	{
		CHECK_ERROR(acclerator, L"TranslateAccelerator not be null.");
		auto it = std::find(acceleratorList_->begin(), acceleratorList_->end(), acclerator);
		if (it != acceleratorList_->end())
		{
			acceleratorList_->erase(it);
			SAFE_DELETE(*it);
		}
	}

	void UIMgr::TranslateAccelerator(MSG *msg)
	{
		CHECK_ERROR(msg, L"Message not be null.");
		for (auto it = acceleratorList_->begin(); it != acceleratorList_->end(); it++)
		{
			(*it)->TranslateAccelerator(msg);
		}
	}

	bool UIMgr::TranslateMessage(const LPMSG pMsg)
	{
		UINT uStyle = GetWindowStyle(pMsg->hwnd);
		UINT uChildRes = uStyle & WS_CHILD;
		LRESULT lRes = 0;

		for (auto it = wndsConfigMap_->begin(); it != wndsConfigMap_->end(); it++)
		{
			auto wc = it->second;
			if (wc && wc->wnd_ && wc->wnd_->GetHWND() == pMsg->hwnd)
			{
				// 处理加速键消息
				TranslateAccelerator(pMsg);

				//  处理FaceUI关心的消息
				if (wc->wnd_->PreHandlerMessage(pMsg->message, pMsg->wParam, pMsg->lParam))
				{
					return true;
				}
			}
		}

		return false;
	}
	
	bool UIMgr::RegisterWndEvent(HWND hwnd, WindowControlEvent *event)
	{
		CHECK_ERROR(hwnd, L"");
		CHECK_ERROR(event, L"");

		auto it = eventMap_->find(hwnd);
		if (it->second)
		{
			return false;
		}

		eventMap_->insert(std::make_pair(hwnd, event));
		return true;
	}

	bool UIMgr::RemoveWndEvent(WindowControlEvent *event)
	{
		CHECK_ERROR(event, L"");

		for (auto it = eventMap_->begin(); it != eventMap_->end(); it++)
		{
			if (it->second == event)
			{
				eventMap_->erase(it);
				return true;
			}
		}

		return false;
	}

	bool UIMgr::RemoveWndEvent(HWND hwnd)
	{
		CHECK_ERROR(hwnd, L"");

		auto it = eventMap_->find(hwnd);
		if (it->second)
		{
			eventMap_->erase(it);
			return true;
		}

		return false;
	}

	WindowControlEvent* UIMgr::GetWndEvent(HWND hwnd)
	{
		CHECK_ERROR(hwnd, L"");

		auto it = eventMap_->find(hwnd);
		if (it->second)
		{
			return it->second;
		}

		return nullptr;
	}

	void UIMgr::NotifyHandler(HWND hwnd, Control* notifyControl, NOTIFY msg, WPARAM wParam /* = 0 */, LPARAM lParam /* = 0 */)
	{
		CHECK_ERROR(hwnd, L"");
		CHECK_ERROR(notifyControl, L"");
		CHECK_ERROR(notifyControl, L"");

		auto handler = GetWndEvent(hwnd);
		if (!handler)
		{
			return;
		}

		TNotify notify;
		notify.pSender = notifyControl;
		notify.type = msg;
		notify.wParam = wParam;
		notify.lParam = lParam;
		Match(msg)
		{
			Case(NOTIFY_LCLICK)
				handler->OnButtonClicked(notify);
			Otherwise()
				handler->Notify(notify);
		}
		EndMatch
	}
}