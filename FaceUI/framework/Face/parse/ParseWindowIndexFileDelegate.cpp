
#include "stdafx.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "ParseWindowIndexFileDelegate.h"

namespace Face
{
	using namespace Face;
	
	ParseResourceIndexFileDelegate::ParseResourceIndexFileDelegate()
	{}

	ParseResourceIndexFileDelegate::~ParseResourceIndexFileDelegate()
	{}

	bool ParseResourceIndexFileDelegate::Parse(FaceString& _strPath)
	{
		CHECK_ERROR(_strPath.Length(), L"The resource index file is null.");
		FaceFilePath path(_strPath);
		CHECK_ERROR(!path.IsFolder(), L"The resource index file is folder.");
		FaceFile file(path);
		CHECK_ERROR(file.Exists(), L"The resource index file is not exists.");
		_Parse(_strPath);

		return  true;
	}

	void ParseResourceIndexFileDelegate::_Parse(FaceString& _strPath)
	{
		using namespace rapidxml;

		rapidxml::file<wchar_t> xml(FaceString::W2A(_strPath.Buffer()).c_str());
		CHECK_ERROR(xml.size(), L"Error in resource.xml file.");
		xml_document<wchar_t> doc;
		doc.parse<0>(xml.data());
		xml_node<wchar_t> *root = doc.first_node(L"Component");
		CHECK_ERROR(root, L"Error in resource.xml file.");
		xml_node<wchar_t> *wndNode = root->first_node(L"Windows");
		xml_node<wchar_t> *fontNode = root->first_node(L"Fonts");
		
		CHECK_ERROR(wndNode, L"Error in resource.xml file.");
		CHECK_ERROR(fontNode, L"Error in resource.xml file.");
		
		auto fn = [](FaceWindowObject *wo, const wchar_t *name, const wchar_t *value) 
		{
			if (wcscmp(name, L"style") == 0)
			{
				Match(value)
				{
					Case(L"UI_WNDSTYLE_FRAME")
						wo->style = UI_WNDSTYLE_EX_FRAME;
					Case(L"UI_WNDSTYLE_CHILD")
						wo->style = UI_WNDSTYLE_CHILD;
					Case(L"UI_WNDSTYLE_DIALOG")
						wo->style = UI_WNDSTYLE_DIALOG;
					Otherwise()
						wo->style = UI_WNDSTYLE_CONTAINER;
				}
				EndMatch
			}
			else if (wcscmp(name, L"exstyle") == 0)
			{
				Match(value)
				{
					Case(L"UI_WNDSTYLE_EX_FRAME")
						wo->exStyle = UI_WNDSTYLE_EX_FRAME;
					Case(L"UI_WNDSTYLE_EX_DIALOG")
						wo->exStyle = UI_WNDSTYLE_EX_DIALOG;
					Otherwise()
						wo->exStyle = 0;
				}
				EndMatch
			}
		};
		for (xml_node<wchar_t> *node = wndNode->first_node(); node != nullptr; node = node->next_sibling())
		{
			auto pwo = new FaceWindowObject;
			pwo->isMainWnd = wcscmp(node->name(), L"MainWindow") == 0 ? true:false;
			for (xml_attribute<wchar_t> *attr = node->first_attribute(); attr != nullptr; attr = attr->next_attribute())
			{
				Match(attr->name())
				{
					Case(L"name")
						pwo->wndName = attr->value();
					Case(L"classname")	
						pwo->wndClassName = attr->value();
					Case(L"event")	
						pwo->wndEventClass = attr->value();
					Case(L"file")	
						wchar_t wszFile[MAX_PATH] = { 0 };
						PathCombine(wszFile, FaceApp::getInstance()->GetResourcePath().GetFullPath().Buffer(), attr->value());
						pwo->wndFile = wszFile;
					Case(L"style")
						fn(pwo, L"style", attr->value());
					Case(L"exstyle")
						fn(pwo, L"exstyle", attr->value());
				}
				EndMatch

				CHECK_ERROR(pwo->wndName.Length(), L"Error in resource.xml");
				CHECK_ERROR(pwo->wndClassName.Length(), L"Error in resource.xml");
				CHECK_ERROR(pwo->wndEventClass.Length(), L"Error in resource.xml");
				CHECK_ERROR(pwo->wndFile.Length(), L"Error in resource.xml");
			}
			FaceWndsMgr::getInstance()->AddWindow(pwo->wndClassName.Buffer(), pwo);
		}

		for (xml_node<wchar_t> *node = fontNode->first_node(); node != nullptr; node = node->next_sibling())
		{
			auto pFont = new FaceFontObject;
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
			FaceFontsMgr::getInstance()->AddFont(pFont->name.Buffer(), pFont);
		}
	}
}


