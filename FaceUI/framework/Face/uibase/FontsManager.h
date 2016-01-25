
#ifndef _FONTSMANAGER_H_
#define _FONTSMANAGER_H_

#pragma once

namespace Face
{
	class FontConfig;
	class FACE_API FontsMgr : public Singleton<FontsMgr>
	{
	public:
		virtual void Init();
		virtual void Destory();

		void AddFont(const wchar_t* _pwszFontId, FontConfig* _pFont);
		HFONT GetFont(String& _fontId);
		TEXTMETRIC& GetTextMetric(String& _fontId);

	private:
		typedef std::unordered_map<const wchar_t*, FontConfig*> FontsObjectMap;
		FontsObjectMap* fontsMap_;
	};
}

#endif