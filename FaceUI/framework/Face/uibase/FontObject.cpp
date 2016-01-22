#include "stdafx.h"
#include "FontObject.h"

namespace Face
{
	FaceFontObject::FaceFontObject()
		:size(0),
		bBold(false),
		bItalic(false),
		bUnderline(false),
		bStrikeout(false),
		name(L""),
		faceName(L""),
		_hFont(nullptr)
	{
		::ZeroMemory(&_textMetric, sizeof(TEXTMETRIC));
	}

	HFONT FaceFontObject::GetFont()
	{
		CHECK_ERROR(faceName.Length(), L"");
		if (_hFont)
		{
			return _hFont;
		}

		LOGFONT lf = { 0 };
		::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
		wcscpy_s(lf.lfFaceName, faceName.Buffer());
		lf.lfCharSet = DEFAULT_CHARSET;
		lf.lfHeight = -size;
		if (bBold)
		{
			lf.lfWeight += FW_BOLD;
		}

		if (bUnderline)
		{
			lf.lfUnderline = TRUE;
		}

		if (bItalic)
		{
			lf.lfItalic = TRUE;
		}

		if (bStrikeout)
		{
			lf.lfStrikeOut = TRUE;
		}

		_hFont = ::CreateFontIndirect(&lf);
		return _hFont;
	}

	FaceFontObject::~FaceFontObject()
	{
		if (_hFont != nullptr)
		{
			::DeleteObject(_hFont);
		}
	}

	TEXTMETRIC& FaceFontObject::GetTextMetric()
	{
		return _textMetric;
	}
}

