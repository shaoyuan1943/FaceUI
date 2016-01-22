
#include "stdafx.h"

namespace Face
{
	void FaceWndsMgr::Init()
	{
		windowsObejctMap_ = new WindowsObjectMap;
		windowsListenerMap_ = new WindowsMessageListenersMap;
	}

	void FaceWndsMgr::Destory()
	{
		SAFE_DELETE(windowsObejctMap_);
	}

	void FaceWndsMgr::AddWindow(const wchar_t* wndClassName, FaceWindowObject* _pWo)
	{
		CHECK_ERROR(wndClassName, L"");
		CHECK_ERROR(_pWo, L"");

		windowsObejctMap_->insert(std::make_pair(wndClassName, _pWo));
	}

	void FaceWndsMgr::RegisterMessageListener(const wchar_t* wndClassName, FaceMessageListener *listener)
	{
		CHECK_ERROR(wndClassName, L"");
		CHECK_ERROR(listener, L"");

		windowsListenerMap_->insert(std::make_pair(wndClassName, listener));
	}

	FaceMessageListener* FaceWndsMgr::GetMessageListener(const wchar_t *wndClassName)
	{
		CHECK_ERROR(wndClassName, L"");

		auto it = windowsListenerMap_->find(wndClassName);
		if (it == windowsListenerMap_->end())
		{
			return nullptr;
		}

		return it->second;
	}

	FaceWindowObject* FaceWndsMgr::GetWindowObject(const wchar_t* wndClassName)
	{
		CHECK_ERROR(wndClassName, L"");
		auto it = windowsObejctMap_->find(wndClassName);
		if (it == windowsObejctMap_->end())
		{
			return nullptr;
		}

		return it->second;
	}

	FaceWindowObject* FaceWndsMgr::GetMainWindowObject()
	{
		for (auto it = windowsObejctMap_->begin(); it != windowsObejctMap_->end(); it++)
		{
			auto wo = it->second;
			if (wo->isMainWnd)
			{
				return wo;
			}
		}

		return nullptr;
	}
}