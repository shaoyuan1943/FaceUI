#ifndef _PARSEWINDOWINDEXFILEDELEGATE_H_
#define _PARSEWINDOWINDEXFILEDELEGATE_H_
/*
	解析windows.xml文件，将配置的window类名以及对应的xml文件解析成templateobject
*/

class TemplateObject;
namespace Face
{
	using namespace std;
	class ParseResourceIndexFileDelegate : public Face::FaceObject, Face::FaceNotCopyable
	{
	public:
		ParseResourceIndexFileDelegate();
		virtual ~ParseResourceIndexFileDelegate();
	
	public:
		bool Parse(FaceString& _strPath);

	private:
		void _Parse(FaceString& _strPath);
	
	};
}
#endif //_PARSEWINDOWINDEXFILEDELEGATE_H_