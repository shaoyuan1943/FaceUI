

#ifndef _FACE_OBJECT_H_
#define _FACE_OBJECT_H_

#pragma once

namespace Face
{
	class FACE_API FaceObject
	{
	public:
		virtual ~FaceObject();
	};

	class FACE_API FaceNotCopyable
	{
	private:
		FaceNotCopyable(const FaceNotCopyable&);
		FaceNotCopyable& operator=(const FaceNotCopyable&);
	public:
		FaceNotCopyable();
	};

	class FACE_API FaceError
	{
	private:
		const wchar_t* description;
	public:
		FaceError(const wchar_t* _description);
		const wchar_t* Description()const;
	};
}


#endif