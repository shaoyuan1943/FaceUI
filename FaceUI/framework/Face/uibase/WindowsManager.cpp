#include "stdafx.h"

namespace Face
{
	void WndsMgr::Init()
	{
		wndsConfigMap_ = new WndsConfigMap;
	}

	void WndsMgr::Destory()
	{
		SAFE_DELETE(wndsConfigMap_);
	}

	void WndsMgr::AddWndConfig(LPCTSTR wndClassName, WndConfig* _pWo)
	{
		CHECK_ERROR(wndClassName, L"");
		CHECK_ERROR(_pWo, L"");

		wndsConfigMap_->insert(std::make_pair(wndClassName, _pWo));
	}

	void WndsMgr::OnWndFinalMessage(LPCTSTR wndClassName)
	{
		CHECK_ERROR(wndClassName, L"");
		CHECK_ERROR(wndClassName != L"", L"");

		auto wo = GetWndConfig(wndClassName);
		SAFE_DELETE(wo->wnd_);
		SAFE_DELETE(wo->listener_);

		wo->wnd_ = nullptr;
		wo->listener_ = nullptr;
	}

	MessageListener* WndsMgr::GetMessageListener(LPCTSTR wndClassName)
	{
		CHECK_ERROR(wndClassName, L"");
		CHECK_ERROR(wndClassName != L"", L"");

		auto it = wndsConfigMap_->find(wndClassName);
		if (it != wndsConfigMap_->end())
		{
			return it->second->listener_;
		}

		return nullptr;
	}

	WndConfig* WndsMgr::GetWndConfig(LPCTSTR wndClassName)
	{
		CHECK_ERROR(wndClassName, L"");
		auto it = wndsConfigMap_->find(wndClassName);
		if (it != wndsConfigMap_->end())
		{
			return it->second;
		}

		return nullptr;
	}

	WndConfig* WndsMgr::GetMainWndConfig()
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

	void WndsMgr::ShowWindow(LPCTSTR wndClassName, MessageListener *listener, bool bShow/* = true */, bool bTakeFocus/* = true */)
	{
		CHECK_ERROR(wndClassName, L"");
		CHECK_ERROR(wndClassName != L"", L"");
		CHECK_ERROR(listener, L"");

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
			config->listener_ = listener;
			config->wnd_ = wndImpl;
			wndImpl->Create(nullptr, wndClassName, config->wndName_.Buffer(), L"", config->style_, config->exStyle_, config->classStyle_);
			wndImpl->ShowWindow();
			// TODO：进入消息循环
		}
	}

	fuint WndsMgr::ShowModal(HWND hParent, LPCTSTR wndClassName, MessageListener *listener)
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
			config->listener_ = listener;
			config->wnd_ = wndImpl;
			wndImpl->Create(nullptr, wndClassName, config->wndName_.Buffer(), L"", config->style_, config->exStyle_, config->classStyle_);
			return wndImpl->ShowModal();
		}
		return IDCANCEL;
	}

	void WndsMgr::CloseWindow(fuint ret/* = IDOK */)
	{}
}