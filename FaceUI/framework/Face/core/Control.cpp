#include "stdafx.h"

namespace Face
{
	REGISTER_CREATER(Control, L"Control");

	Control::Control()
	{
		Face::UIMgr::ControlFactory<Control>(L"343");
	}

	Control::~Control()
	{}

	LPVOID Control::GetInterface(LPCTSTR pstrName)
	{
		if (pstrName == L"Control")
		{
			return this;
		}

		return nullptr;
	}

	void Control::EventHandler(TEvent& event)
	{
		bool bHandled = false;
		NOTIFY notify = NOTIFY::NOTIFY_UNKNOW;
		switch (event.type)
		{
			case EVENT_SETCURSOR:
			{
				::SetCursor(::LoadCursor(nullptr, MAKEINTRESOURCE(IDC_ARROW)));
				bHandled = true;
				break;
			}
			case EVENT_KEYUP:
			{

				UIMgr::getInstance()->NotifyHandler(wc_->GetHWND(), this, notify, event.wParam, event.lParam);
				break;
			}
			case EVENT_SETFOCUS:
			{
				focused_ = true;
				break;
			}
			case EVENT_KILLFOCUS:
			{
				focused_ = false;
				break;
			}
			default:
				break;
		}

		if (bHandled)
		{
			return;
		}

		if (parent_ != nullptr)
		{
			parent_->EventHandler(event);
		}
	}

	void Control::Invalidate()
	{

	}

	void Control::SetAttribute(LPCTSTR key, LPCTSTR value)
	{

	}
}