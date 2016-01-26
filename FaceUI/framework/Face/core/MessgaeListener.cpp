#include "stdafx.h"

namespace Face
{
	MessageListener::MessageListener()
	{}

	MessageListener::~MessageListener()
	{}

	void MessageListener::OnFinalMessage(HWND hWnd)
	{

	}

	LRESULT MessageListener::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	void MessageListener::OnWndCreated()
	{}

	void MessageListener::OnWndClose()
	{}

	void MessageListener::OnWndDestory()
	{}

	void MessageListener::OnWndSize()
	{}

	void MessageListener::OnChar(WPARAM code)
	{}

	void MessageListener::OnKeyDown(WPARAM code)
	{}

	void MessageListener::OnSysCommand(WPARAM code)
	{}
}