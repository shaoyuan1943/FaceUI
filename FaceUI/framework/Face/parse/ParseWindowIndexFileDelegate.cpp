
#include "stdafx.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "ParseWindowIndexFileDelegate.h"
#include "match.hpp"

namespace Face
{
	using namespace Face;
	
	ParseResourceIndexFileDelegate::ParseResourceIndexFileDelegate()
	{}

	ParseResourceIndexFileDelegate::~ParseResourceIndexFileDelegate()
	{}

	bool ParseResourceIndexFileDelegate::Parse(String& _strPath)
	{
		CHECK_ERROR(_strPath.Length(), L"The resource index file is null.");
		FilePath path(_strPath);
		CHECK_ERROR(!path.IsFolder(), L"The resource index file is folder.");
		File file(path);
		CHECK_ERROR(file.Exists(), L"The resource index file is not exists.");
		_Parse(_strPath);

		return  true;
	}

	void ParseResourceIndexFileDelegate::_Parse(String& _strPath)
	{
		using namespace rapidxml;

		rapidxml::file<wchar_t> xml(String::W2A(_strPath.Buffer()).c_str());
		CHECK_ERROR(xml.size(), L"Error in resource.xml file.");
		xml_document<wchar_t> doc;
		doc.parse<0>(xml.data());
		rapidxml::xml_node<wchar_t> *root = doc.first_node(L"Component");
		CHECK_ERROR(root, L"Error in resource.xml file.");
		rapidxml::xml_node<wchar_t> *wndNode = root->first_node(L"Windows");
		rapidxml::xml_node<wchar_t> *fontNode = root->first_node(L"Fonts");
		
		CHECK_ERROR(wndNode, L"Error in resource.xml file.");
		CHECK_ERROR(fontNode, L"Error in resource.xml file.");
		
		auto fn = [](WndConfig *wo, const wchar_t *name, const wchar_t *value) 
		{
			if (wcscmp(name, L"style") == 0)
			{
				Match(value)
				{
					Case(L"UI_WNDSTYLE_FRAME")
						wo->style_ = UI_WNDSTYLE_EX_FRAME;
					Case(L"UI_WNDSTYLE_CHILD")
						wo->style_ = UI_WNDSTYLE_CHILD;
					Case(L"UI_WNDSTYLE_DIALOG")
						wo->style_ = UI_WNDSTYLE_DIALOG;
					Otherwise()
						wo->style_ = UI_WNDSTYLE_CONTAINER;
				}
				EndMatch
			}
			else if (wcscmp(name, L"exstyle") == 0)
			{
				Match(value)
				{
					Case(L"UI_WNDSTYLE_EX_FRAME")
						wo->exStyle_ = UI_WNDSTYLE_EX_FRAME;
					Case(L"UI_WNDSTYLE_EX_DIALOG")
						wo->exStyle_ = UI_WNDSTYLE_EX_DIALOG;
					Otherwise()
						wo->exStyle_ = 0;
				}
				EndMatch
			}
			else if (wcscmp(name, L"classstyle") == 0)
			{
				Match(value)
				{
					Case(L"UI_CLASSSTYLE_FRAME")
						wo->classStyle_ = UI_CLASSSTYLE_FRAME;
					Case(L"UI_CLASSSTYLE_CHILD")
						wo->classStyle_ = UI_CLASSSTYLE_CHILD;
					Case(L"UI_CLASSSTYLE_DIALOG")
						wo->classStyle_ = UI_CLASSSTYLE_DIALOG;
					Otherwise()
						wo->classStyle_ = 0;
				}
				EndMatch
			}
		};
		for (rapidxml::xml_node<wchar_t> *node = wndNode->first_node(); node != nullptr; node = node->next_sibling())
		{
			auto pwo = new WndConfig;
			pwo->isMainWnd_ = wcscmp(node->name(), L"MainWindow") == 0 ? true:false;
			for (xml_attribute<wchar_t> *attr = node->first_attribute(); attr != nullptr; attr = attr->next_attribute())
			{
				Match(attr->name())
				{
					Case(L"name")
						pwo->wndName_ = attr->value();
					Case(L"classname")	
						pwo->wndClassName_ = attr->value();
					Case(L"file")	
						wchar_t wszFile[MAX_PATH] = { 0 };
						PathCombine(wszFile, App::getInstance()->GetResourcePath().GetFullPath().Buffer(), attr->value());
						pwo->wndXmlFile_ = wszFile;
					Case(L"style")
						fn(pwo, L"style", attr->value());
					Case(L"exstyle")
						fn(pwo, L"exstyle", attr->value());
					Case(L"classstyle")
						fn(pwo, L"classstyle", attr->value());
				}
				EndMatch

				CHECK_ERROR(pwo->wndName_.Length(), L"Error in resource.xml");
				CHECK_ERROR(pwo->wndClassName_.Length(), L"Error in resource.xml");
				CHECK_ERROR(pwo->wndXmlFile_.Length(), L"Error in resource.xml");
			}
			UIMgr::getInstance()->AddWndConfig(pwo->wndClassName_.Buffer(), pwo);
		}

		for (rapidxml::xml_node<wchar_t> *node = fontNode->first_node(); node != nullptr; node = node->next_sibling())
		{
			auto pFont = new FontConfig;
			for (xml_attribute<wchar_t> *attr = node->first_attribute(); attr != nullptr; attr = attr->next_attribute())
			{
				Match(attr->name())
				{
					Case(L"name") 	
						pFont->name = attr->value();
					Case(L"face")	
						pFont->faceName = attr->value();
					Case(L"size")	
						pFont->size = _wtoi(attr->value());
					Case(L"underline") 
						pFont->bUnderline = _wtoi(attr->value()) > 0 ? true : false;
					Case(L"bold")	
						pFont->bBold = _wtoi(attr->value()) > 0 ? true : false;
					Case(L"italic") 
						pFont->bItalic = _wtoi(attr->value()) > 0 ? true : false;
					Case(L"strikeout") 
						pFont->bStrikeout = _wtoi(attr->value()) > 0 ? true : false;
				}
				EndMatch
			}
			FontsMgr::getInstance()->AddFont(pFont->name.Buffer(), pFont);
		}
	}
}


