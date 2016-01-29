#include "stdafx.h"

namespace Face
{
	Control::Control()
	{}

	Control::~Control()
	{}

	void Control::EventHandler(TEvent& event)
	{
		bool bHandled = false;
		switch (event.Type)
		{
			case EVENT_SETCURSOR:
			{
				::SetCursor(::LoadCursor(nullptr, MAKEINTRESOURCE(IDC_ARROW)));
				bHandled = true;
				break;
			}
			case EVENT_KEYUP:
			{
				WndsMgr::getInstance()->NotifyHandler(wc_->GetHWND(), this, 123, event.wParam, event.lParam);
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
}