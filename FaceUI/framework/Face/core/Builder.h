#pragma once
#ifndef _BUILDER_H_
#define _BUILDER_H_

namespace Face
{
	class Control;
	class FACE_API ICustomBuilder : public NotCopyable
	{
	public:
		virtual Control* CreateCustomControls(LPCTSTR pstrClass) = 0;
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
		Control* Create(LPCTSTR psz, ICustomBuilder *customBuilder = nullptr);
	};
}
#endif