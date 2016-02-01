#include "stdafx.h"
#include "TemplateObject.h"

namespace Face
{
	TemplateObject::TemplateObject()
	{}

	TemplateObject::~TemplateObject()
	{
		for (auto it = childsList_.begin(); it != childsList_.end(); it++)
		{
			auto templ = *it;
			SAFE_DELETE(templ);
		}

		childsList_.clear();
	}

	void TemplateObject::SetType(LPCTSTR pszType)
	{
		type = pszType;
	}

	LPCTSTR TemplateObject::GetType()
	{
		return type.Buffer();
	}

	void TemplateObject::SetAttribute(LPCTSTR key, LPCTSTR value)
	{
		attributeMap_[key] = value;
	}

	LPCTSTR TemplateObject::GetAttribute(LPCTSTR key)
	{
		auto it = attributeMap_.find(key);
		if (it != attributeMap_.end())
		{
			return it->second.Buffer();
		}

		return nullptr;
	}

	int TemplateObject::GetChildCount()
	{
		return childsList_.size();
	}

	TemplateObject* TemplateObject::GetChild(unsigned int index)
	{
		int i = 0;
		if (index >= 0 && childsList_.size() > index)
		{
			for (auto it = childsList_.begin(); it != childsList_.end(); it++, i++)
			{
				if (index == i)
				{
					return *it;
				}
			}
		}

		return nullptr;
	}

	void TemplateObject::InsertChild(TemplateObject *child, int index /* = -1 */)
	{
		int i = 0;
		if (index == -1)
		{
			childsList_.push_back(child);
		}
		else
		{
			auto tagIt = childsList_.begin();
			for (auto it = childsList_.begin(); it != childsList_.end(); it++, i++)
			{
				if (i = index)
				{
					tagIt = it;
					break;
				}
			}

			childsList_.insert(tagIt, child);
		}
	}
}