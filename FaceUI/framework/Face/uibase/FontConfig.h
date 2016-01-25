
#ifndef _FONTCONFIG_H_
#define _FONTCONFIG_H_

#pragma once

namespace Face
{
	class FACE_API FontConfig : public Object
	{
	public:
		FontConfig();
		virtual ~FontConfig();

		WString name;
		WString faceName;
		fint size;
		bool bBold;
		bool bItalic;
		bool bUnderline;
		bool bStrikeout;

		HFONT GetFont();
		TEXTMETRIC& GetTextMetric();

	private:
		HFONT _hFont;
		TEXTMETRIC _textMetric;
	};
}

#endif // _FONTCONFIG_H_
