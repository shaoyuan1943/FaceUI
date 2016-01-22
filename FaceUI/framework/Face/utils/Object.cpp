
#include "stdafx.h"
#include "Object.h"

namespace Face
{
	FaceObject::~FaceObject()
	{
	}

	FaceNotCopyable::FaceNotCopyable()
	{
	}

	FaceNotCopyable::FaceNotCopyable(const FaceNotCopyable&)
	{
	}

	FaceNotCopyable& FaceNotCopyable::operator=(const FaceNotCopyable&)
	{
		return *this;
	}

	FaceError::FaceError(const wchar_t* _description)
	{
		description = _description;
	}

	const wchar_t* FaceError::Description()const
	{
		return description;
	}
}
