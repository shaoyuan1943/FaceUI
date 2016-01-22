
#ifndef _FONTSMANAGER_H_
#define _FONTSMANAGER_H_

#pragma once

namespace Face
{
	class FaceFontObject;
	class FACE_API FaceFontsMgr : public FaceSingleton<FaceFontsMgr>
	{
	public:
		virtual void Init();
		virtual void Destory();

		void AddFont(const wchar_t* _pwszFontId, FaceFontObject* _pFont);
		HFONT GetFont(FaceString& _fontId);
		TEXTMETRIC& GetTextMetric(FaceString& _fontId);

	private:
		typedef std::unordered_map<const wchar_t*, FaceFontObject*> FontsObjectMap;
		FontsObjectMap* fontsMap_;
	};
}

#endif