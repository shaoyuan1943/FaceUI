#include "stdafx.h"
#include "ParseWindowIndexFileDelegate.h"

namespace Face
{
	void FaceApp::Init()
	{
		parseDelegate_ = new ParseResourceIndexFileDelegate;
		wchar_t szPath[MAX_PATH] = { 0 };
		::GetModuleFileName(nullptr, szPath, MAX_PATH);
		instancePath_ = szPath;
	}

	void FaceApp::Destory()
	{
		SAFE_DELETE(parseDelegate_);
	}

	void FaceApp::SetResourcePath(FaceFilePath& _path)
	{
		CHECK_ERROR(_path.IsFolder(), L"The skin path is not dirs");
		FaceString path = _path.GetFullPath();
		path = path + L"\\resource.xml";
		CHECK_ERROR(FaceFile(path).Exists(), L"The resource.xml is not exist");
		skinPath_ = _path;

		parseDelegate_->Parse(path);
	}

	FaceFilePath& FaceApp::GetResourcePath()
	{
		return skinPath_;
	}

	FaceFilePath& FaceApp::GetInstancePath()
	{
		return instancePath_;
	}

	FaceWindowImpl* FaceApp::GetWindowImpl(const wchar_t* wndClassName)
	{
		CHECK_ERROR(wndClassName, L"");
		auto wo = FaceWndsMgr::getInstance()->GetWindowObject(wndClassName);
		return wo->wnd;
	}

	void FaceApp::Run()
	{
		auto wo = FaceWndsMgr::getInstance()->GetMainWindowObject();
		CHECK_ERROR(wo, L"Not main window.");


	}

	void FaceApp::SetInstance(HINSTANCE instance)
	{
		if (instance != instance_)
		{
			instance_ = instance;
		}
	}

	HINSTANCE FaceApp::GetAppInstance()
	{
		return instance_;
	}

}