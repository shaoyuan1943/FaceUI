#include "stdafx.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "TemplateObject.h"

namespace Face
{
	typedef rapidxml::xml_node<wchar_t> Node;
	typedef rapidxml::xml_attribute<wchar_t> Attr;
	TemplateObject* _Parser(rapidxml::xml_node<wchar_t> *node, TemplateObject *parent)
	{
		CHECK_ERROR(node->name() || node->name() == L"", L"");
		TemplateObject *childTemplate = new TemplateObject;
		childTemplate->SetType(node->name());
		for (Attr *attr = node->first_attribute(); attr != nullptr; attr = attr->next_attribute())
		{
			CHECK_ERROR(attr->name() || attr->name() == L"", L"");
			CHECK_ERROR(attr->value() || attr->value() == L"", L"");
			childTemplate->SetAttribute(attr->name(), attr->value());
		}

		for (auto element = node->first_node(); element != nullptr; element = element->next_sibling())
		{
			_Parser(element, childTemplate);
		}

		if (parent == nullptr)
		{
			return childTemplate;
		}
		else
		{
			parent->InsertChild(childTemplate, -1);
		}

		return nullptr;
	}

	XMLBuilder::XMLBuilder()
	{}

	XMLBuilder::~XMLBuilder()
	{}

	void XMLBuilder::Init()
	{}

	void XMLBuilder::Destory()
	{}

	Control* XMLBuilder::Create(LPCTSTR psz, WindowControl *wc)
	{
		CHECK_ERROR(wc, L"");
		ParserType parserType = _GetParserType(psz);
		if (parserType == FROM_NONE)
		{
			return nullptr;
		}

		TemplateObject *templ = nullptr;
		auto it = xmlTemplateMap_.find(psz);
		if (it != xmlTemplateMap_.end())
		{
			templ = it->second;
			return _Create(templ, wc);
		}

		switch (parserType)
		{
			case Face::FROM_WNDCLASSNAME:
			{
				auto wndConfig = UIMgr::getInstance()->GetWndConfig(psz);
				if (!wndConfig)
				{
					return nullptr;
				}

				templ = _ParseByXMLFile(wndConfig->GetWndXMLFile());
				return _Create(templ, wc);
			}
			case Face::FROM_XMLFILE:
			{
				FilePath path(App::getInstance()->GetResourcePath().GetFullPath() + psz);
				if (path.IsFile())
				{
					templ = _ParseByXMLFile(path.GetFullPath());
					return _Create(templ, wc);
				}
				return nullptr;
			}
			case Face::FROM_XMLCONTENT:
			{
				LPTSTR content = const_cast<LPTSTR>(psz);
				templ = _ParseByXMLContent(content);
				return _Create(templ, wc);
			}
			default:
				return nullptr;
		}

		return nullptr;
	}

	ParserType XMLBuilder::_GetParserType(LPCTSTR psz)
	{
		ParserType parserType = FROM_NONE;
		auto wc = UIMgr::getInstance()->GetWndConfig(psz);
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

	TemplateObject* XMLBuilder::_ParseByXMLContent(LPTSTR content)
	{
		using namespace rapidxml;

		xml_document<wchar_t> doc;
		doc.parse<0>(content);
		Node *root = doc.first_node();
		CHECK_ERROR(root, L"Error in window file.");

		return _Parser(root, nullptr);
	}

	TemplateObject* XMLBuilder::_ParseByXMLFile(const WString& xmlFile)
	{
		using namespace rapidxml;
		
		rapidxml::file<wchar_t> xml(String::W2A(xmlFile.Buffer()).c_str());
		CHECK_ERROR(xml.size(), L"Error in window file.");
		xml_document<wchar_t> doc;
		doc.parse<0>(xml.data());
		Node *root = doc.first_node();
		CHECK_ERROR(root, L"Error in xml file.");

		auto templ = _Parser(root, nullptr);
		if (templ)
		{
			xmlTemplateMap_.insert(std::make_pair(xmlFile.Buffer(), templ));
		}

		return templ;
	}

	Control* XMLBuilder::_Create(TemplateObject *templateObject, WindowControl *wc, Control *parent)
	{
		Control *control = nullptr;
		if (templateObject->GetType() == L"Window")
		{
			auto begin = templateObject->attributeMap_.begin();
			auto end = templateObject->attributeMap_.end();
			while (begin != end)
			{
				wc->SetAttribute(begin->first.Buffer(), begin->second.Buffer());
				++begin;
			}
			templateObject = templateObject->GetChild(0);
		}

		control = UIMgr::getInstance()->CreateControl(templateObject->GetType());
		CHECK_ERROR(control, L"");
		control->SetWindowControl(wc);
		auto begin = templateObject->attributeMap_.begin();
		auto end = templateObject->attributeMap_.end();
		while (begin != end)
		{
			control->SetAttribute(begin->first.Buffer(), begin->second.Buffer());
			++begin;
		}

		int childCount = templateObject->GetChildCount();
		IContainer *container = static_cast<IContainer*>(control->GetInterface(L"IContainer"));
		if (container && childCount > 0)
		{
			for (int i = 0; i < childCount; i++)
			{
				Control *childControl = this->_Create(templateObject->GetChild(i), wc, control);
				if (childControl)
				{
					container->Add(childControl);
				}
			}
		}
		
		return control;
	}
}