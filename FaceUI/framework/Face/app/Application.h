
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#pragma once

namespace Face
{
	class FaceWindowImpl;
	class ParseResourceIndexFileDelegate;
	class FACE_API FaceApp : public FaceSingleton<FaceApp>
	{
	public:
		virtual void Init();
		virtual void Destory();
	/*
		以下是接口
	*/
	public:
		void SetResourcePath(FaceFilePath& _path);
		FaceFilePath& GetResourcePath();

		FaceFilePath& GetInstancePath();
		void SetInstance(HINSTANCE instance);
		HINSTANCE GetAppInstance();
		FaceWindowImpl* GetWindowImpl(const wchar_t* wndClassName);

		void Run();
	private:
		FaceFilePath skinPath_;
		ParseResourceIndexFileDelegate* parseDelegate_{ nullptr };
		FaceFilePath instancePath_;
		HINSTANCE instance_;
	};
}

#endif