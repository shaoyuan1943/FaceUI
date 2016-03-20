
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#pragma once

namespace Face
{
	class WindowImpl;
	class ParseResourceIndexFileDelegate;
	class FACE_API App : public Singleton<App>
	{
	public:
		virtual void Init();
		virtual void Destory();
	/*
		以下是接口
	*/
	public:
		void SetResourcePath(FilePath& _path);
		FilePath& GetResourcePath();
		FilePath& GetInstancePath();
		SYNTHESIZE_PRO(HINSTANCE, instance_, AppInstance);
		WString GetFullPathByName(WString& path);
		void Run();
	private:
		FilePath skinPath_;
		ParseResourceIndexFileDelegate* parseDelegate_{ nullptr };
		FilePath instancePath_;
	};
}

#endif