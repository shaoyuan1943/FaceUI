
#ifndef _FONTOBJECT_H_
#define _FONTOBJECT_H_

#pragma once

namespace Face
{
	class FACE_API FaceFontObject : public Face::FaceObject
	{
	public:
		FaceFontObject();
		virtual ~FaceFontObject();

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

#endif // _FONTOBJECT_H_
