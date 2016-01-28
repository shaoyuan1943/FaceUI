#include "stdafx.h"

namespace Face
{
	XMLBuilder::XMLBuilder()
	{}

	XMLBuilder::~XMLBuilder()
	{}

	void XMLBuilder::Init()
	{}

	void XMLBuilder::Destory()
	{}

	Control* XMLBuilder::Create(LPCTSTR psz, ICustomBuilder *customBuilder/* = nullptr */)
	{
		ParserType parserType = _GetParserType(psz);
		if (parserType == FROM_NONE)
		{
			return nullptr;
		}


		return nullptr;
	}

	ParserType XMLBuilder::_GetParserType(LPCTSTR psz)
	{
		ParserType parserType = FROM_NONE;
		auto wc = WndsMgr::getInstance()->GetWndConfig(psz);
		if (wc)
		{
			parserType = FROM_WNDCLASSNAME;
			return parserType;
		}

		if (psz[0] == L'<')
		{
			parserType = FROM_XMLCONTENT;
			return parserType;
		}

		WString file = App::getInstance()->GetResourcePath().GetFullPath() + psz;
		if (FilePath(file).IsFile())
		{
			parserType = FROM_XMLFILE;
		}
		else
		{
			parserType = FROM_NONE;
		}
		return parserType;
	}
}