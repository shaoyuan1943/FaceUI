#include "stdafx.h"
#include "ParseWindowIndexFileDelegate.h"

namespace Face
{
	void App::Init()
	{
		parseDelegate_ = new ParseResourceIndexFileDelegate;
		wchar_t szPath[MAX_PATH] = { 0 };
		::GetModuleFileName(nullptr, szPath, MAX_PATH);
		instancePath_ = szPath;
	}

	void App::Destory()
	{
		SAFE_DELETE(parseDelegate_);
	}

	void App::SetResourcePath(FilePath& _path)
	{
		CHECK_ERROR(_path.IsFolder(), L"The skin path is not dirs");
		WString path = _path.GetFullPath();
		path = path + L"\\resource.xml";
		CHECK_ERROR(File(path).Exists(), L"The resource.xml is not exist");
		skinPath_ = _path;

		parseDelegate_->Parse(path);
	}

	FilePath& App::GetResourcePath()
	{
		return skinPath_;
	}

	FilePath& App::GetInstancePath()
	{
		return instancePath_;
	}


	void App::Run()
	{


		WndsMgr::getInstance()->MessageLoop();
	}

	void App::SetInstance(HINSTANCE instance)
	{
		if (instance != instance_)
		{
			instance_ = instance;
		}
	}

	HINSTANCE App::GetAppInstance()
	{
		return instance_;
	}

	// Ïà¶ÔÂ·¾¶
	WString App::GetFullPathByName(WString& path)
	{
		WString full = App::getInstance()->GetResourcePath().GetFullPath();
		full = full + path;
		return full;
	}

	WString App::GetFullPathByName(LPCTSTR path)
	{
		return GetFullPathByName(WString(path));
	}
}