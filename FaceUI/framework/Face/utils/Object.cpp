
#include "stdafx.h"
#include "Object.h"

namespace Face
{
	Object::~Object()
	{
	}

	NotCopyable::NotCopyable()
	{
	}

	NotCopyable::NotCopyable(const NotCopyable&)
	{
	}

	NotCopyable& NotCopyable::operator=(const NotCopyable&)
	{
		return *this;
	}

	Error::Error(const wchar_t* _description)
	{
		description = _description;
	}

	const wchar_t* Error::Description()const
	{
		return description;
	}
}
