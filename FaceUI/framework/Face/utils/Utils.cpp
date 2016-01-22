#include "stdafx.h"

namespace Face
{
	FacePoint::FacePoint()
	{
		x = y = 0;
	}

	FacePoint::FacePoint(const POINT& src)
	{
		x = src.x;
		y = src.y;
	}

	FacePoint::FacePoint(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	FacePoint::FacePoint(LPARAM lParam)
	{
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);
	}

	///////////////////////////////////////////////////
	FaceSize::FaceSize()
	{
		cx = cy = 0;
	}

	FaceSize::FaceSize(const SIZE& src)
	{
		cx = src.cx;
		cy = src.cy;
	}

	FaceSize::FaceSize(const RECT rc)
	{
		cx = rc.right - rc.left;
		cy = rc.bottom - rc.top;
	}

	FaceSize::FaceSize(int _cx, int _cy)
	{
		cx = _cx;
		cy = _cy;
	}

	///////////////////////////////////////////////////
	FaceRect::FaceRect()
	{
		left = top = right = bottom = 0;
	}

	FaceRect::FaceRect(const RECT& src)
	{
		left = src.left;
		top = src.top;
		right = src.right;
		bottom = src.bottom;
	}

	FaceRect::FaceRect(int iLeft, int iTop, int iRight, int iBottom)
	{
		left = iLeft;
		top = iTop;
		right = iRight;
		bottom = iBottom;
	}

	int FaceRect::GetWidth() const
	{
		return right - left;
	}

	int FaceRect::GetHeight() const
	{
		return bottom - top;
	}

	void FaceRect::Empty()
	{
		left = top = right = bottom = 0;
	}

	bool FaceRect::IsNull() const
	{
		return (left == 0 && right == 0 && top == 0 && bottom == 0);
	}

	void FaceRect::Join(const RECT& rc)
	{
		if (rc.left < left) left = rc.left;
		if (rc.top < top) top = rc.top;
		if (rc.right > right) right = rc.right;
		if (rc.bottom > bottom) bottom = rc.bottom;
	}

	void FaceRect::ResetOffset()
	{
		::OffsetRect(this, -left, -top);
	}

	void FaceRect::Normalize()
	{
		if (left > right) { int iTemp = left; left = right; right = iTemp; }
		if (top > bottom) { int iTemp = top; top = bottom; bottom = iTemp; }
	}

	void FaceRect::Offset(int cx, int cy)
	{
		::OffsetRect(this, cx, cy);
	}

	void FaceRect::Inflate(int cx, int cy)
	{
		::InflateRect(this, cx, cy);
	}

	void FaceRect::Deflate(int cx, int cy)
	{
		::InflateRect(this, -cx, -cy);
	}

	void FaceRect::Union(FaceRect& rc)
	{
		::UnionRect(this, this, &rc);
	}
}