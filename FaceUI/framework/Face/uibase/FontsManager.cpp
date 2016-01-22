
#include "stdafx.h"
#include "FontsManager.h"

namespace Face
{
	void FaceFontsMgr::Init()
	{
		fontsMap_ = new FontsObjectMap;
	}

	void FaceFontsMgr::Destory()
	{
		for (auto iter = fontsMap_->begin(); iter != fontsMap_->end(); iter++)
		{
			SAFE_DELETE(iter->second);
		}

		fontsMap_->clear();

		SAFE_DELETE(fontsMap_);
	}

	void FaceFontsMgr::AddFont(const wchar_t* _pwszFontId, FaceFontObject* _pFont)
	{
		CHECK_ERROR(_pwszFontId, L"");
		CHECK_ERROR(_pFont, L"");

		fontsMap_->insert(std::make_pair(_pwszFontId, _pFont));
	}

	HFONT FaceFontsMgr::GetFont(FaceString& _fontId)
	{
		CHECK_ERROR(_fontId.Length(), L"");

		return (*fontsMap_)[_fontId.Buffer()]->GetFont();
	}

	TEXTMETRIC& FaceFontsMgr::GetTextMetric(FaceString& _fontId)
	{	
		CHECK_ERROR(_fontId.Length(), L"");

		return (*fontsMap_)[_fontId.Buffer()]->GetTextMetric();
	}
}