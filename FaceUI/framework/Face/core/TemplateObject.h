#pragma once
#ifndef _TEMPLATEOBJECT_H_
#define _TEMPLATEOBJECT_H_

namespace Face
{
	class TemplateObject
	{
		friend class XMLBuilder;
	public:
		TemplateObject();
		~TemplateObject();

		void SetType(LPCTSTR pszType);
		LPCTSTR GetType();

		void SetAttribute(LPCTSTR key, LPCTSTR value);
		LPCTSTR GetAttribute(LPCTSTR key);

		int GetChildCount();

		TemplateObject* GetChild(int index);

		void InsertChild(TemplateObject *child, int index = -1);
	private:
		typedef std::map<WString, WString> AttributeMap;
		typedef std::list<TemplateObject*> ChildList;

		AttributeMap attributeMap_;
		ChildList childsList_;

		WString type;
	};
}
#endif