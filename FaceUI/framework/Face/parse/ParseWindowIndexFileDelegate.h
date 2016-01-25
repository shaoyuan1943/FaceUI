#ifndef _PARSEWINDOWINDEXFILEDELEGATE_H_
#define _PARSEWINDOWINDEXFILEDELEGATE_H_
/*
	解析windows.xml文件，将配置的window类名以及对应的xml文件解析成templateobject
*/

class TemplateObject;
namespace Face
{
	using namespace std;
	class ParseResourceIndexFileDelegate : public Object, Face::NotCopyable
	{
	public:
		ParseResourceIndexFileDelegate();
		virtual ~ParseResourceIndexFileDelegate();
	
	public:
		bool Parse(String& _strPath);

	private:
		void _Parse(String& _strPath);
	
	};
}
#endif //_PARSEWINDOWINDEXFILEDELEGATE_H_