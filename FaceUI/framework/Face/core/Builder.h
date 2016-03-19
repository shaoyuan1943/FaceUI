#pragma once
#ifndef _BUILDER_H_
#define _BUILDER_H_

namespace Face
{
	class xml_node;
	class Control;
	class TemplateObject;
	class WindowImpl;
	enum ParserType
	{
		FROM_NONE = 1,
		FROM_WNDCLASSNAME,
		FROM_XMLFILE,
		FROM_XMLCONTENT,
	};

	class FACE_API XMLBuilder : public Singleton<XMLBuilder>
	{
	public:
		XMLBuilder();
		virtual ~XMLBuilder();

		virtual void Init();
		virtual void Destory();

		/*
			psz: 窗口类名、xml文件路径、xml文件内容
		*/
		Control* Create(LPCTSTR psz, WindowImpl *wndImpl);

	private:
		ParserType _GetParserType(LPCTSTR psz);
		TemplateObject* _ParseByXMLFile(const WString& xmlFile);
		TemplateObject* _ParseByXMLContent(LPTSTR content);

		Control* _Create(TemplateObject *templateObject, WindowImpl *wndImpl, Control *parent = nullptr);

	private:
		typedef std::map<WString, TemplateObject*> XMLTemplateObjectMap;
		XMLTemplateObjectMap xmlTemplateMap_;
	};
}
#endif