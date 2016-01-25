

#ifndef _FACE_OBJECT_H_
#define _FACE_OBJECT_H_

#pragma once

namespace Face
{
	class FACE_API Object
	{
	public:
		virtual ~Object();
	};

	class FACE_API NotCopyable
	{
	private:
		NotCopyable(const NotCopyable&);
		NotCopyable& operator=(const NotCopyable&);
	public:
		NotCopyable();
	};

	class FACE_API Error
	{
	private:
		const wchar_t* description;
	public:
		Error(const wchar_t* _description);
		const wchar_t* Description()const;
	};
}


#endif