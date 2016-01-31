#include "stdafx.h"

namespace Face
{
	Container::Container()
	{}

	Container::~Container()
	{}

	LPVOID Container::GetInterface(LPCTSTR pstrName)
	{
		if (pstrName == L"Container")
		{
			return nullptr;
		}

		return __super::GetInterface(pstrName);
	}

	void Container::SetAttribute(LPCTSTR key, LPCTSTR value)
	{}

	void Container::EventHandler(TEvent& event)
	{}
}