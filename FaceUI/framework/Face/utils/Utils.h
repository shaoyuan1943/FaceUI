#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_

namespace Face
{
	class FACE_API FacePoint : public tagPOINT
	{
	public:
		FacePoint();
		FacePoint(const POINT& src);
		FacePoint(int x, int y);
		FacePoint(LPARAM lParam);
	};

	class FACE_API FaceSize : public tagSIZE
	{
	public:
		FaceSize();
		FaceSize(const SIZE& src);
		FaceSize(const RECT rc);
		FaceSize(int cx, int cy);
	};

	class FACE_API FaceRect : public tagRECT
	{
	public:
		FaceRect();
		FaceRect(const RECT& src);
		FaceRect(int iLeft, int iTop, int iRight, int iBottom);

		int GetWidth() const;
		int GetHeight() const;
		void Empty();
		bool IsNull() const;
		void Join(const RECT& rc);
		void ResetOffset();
		void Normalize();
		void Offset(int cx, int cy);
		void Inflate(int cx, int cy);
		void Deflate(int cx, int cy);
		void Union(FaceRect& rc);
	};
}
#endif