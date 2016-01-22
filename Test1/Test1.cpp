// Test1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FaceUI.h"
using namespace Face;
using namespace std;
#pragma comment(lib, "FaceUI.lib")

void Test()
{
	WString str = L"chencheng";
	std::cout << "长度：" << str.Length() << endl;
	const wchar_t* ch = str.Buffer();
	int i = 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test();
	return 0;
}

