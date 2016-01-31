#pragma once
#ifndef _TEMPLATEOBJECT_H_
#define _TEMPLATEOBJECT_H_

namespace Face
{
	/*
		一个XML文件都会被解析成TemplateObject，然后再通过TemplateObject解析成Controls，
		而这个TemplateObject可以保存在一个cache里，这样重复创建时直接通过key就可以找到TemplateObject创建Controls
	*/ 
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