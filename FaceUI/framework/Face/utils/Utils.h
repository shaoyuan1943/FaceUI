#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_

namespace Face
{
	class FACE_API Point : public tagPOINT
	{
	public:
		Point();
		Point(const POINT& src);
		Point(int x, int y);
		Point(LPARAM lParam);
	};

	class FACE_API Size : public tagSIZE
	{
	public:
		Size();
		Size(const SIZE& src);
		Size(const RECT rc);
		Size(int cx, int cy);
	};

	class FACE_API Rect : public tagRECT
	{
	public:
		Rect();
		Rect(const RECT& src);
		Rect(int iLeft, int iTop, int iRight, int iBottom);

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
		void Union(Rect& rc);
	};
}
#endif