#pragma once
#ifndef _CONTAINER_H_
#define _CONTAINER_H_

namespace Face
{
	class Control;
	/*
		容器基类，所有的容器必须继承IContainer并实现之
	*/
	class IContainer
	{
	public:
		virtual Control* GetItemAt(int iIndex) const = 0;
		virtual int GetItemIndex(Control* pControl) const = 0;
		virtual bool SetItemIndex(Control* pControl, int iIndex) = 0;
		virtual int GetCount() const = 0;
		virtual bool Add(Control* pControl) = 0;
		virtual bool AddAt(Control* pControl, int iIndex) = 0;
		virtual bool Remove(Control* pControl) = 0;
		virtual bool RemoveAt(int iIndex) = 0;
		virtual void RemoveAll() = 0;
		virtual Control* FindSubControl(LPCTSTR pstrSubControlName) = 0;
	};

	class FACE_API Container : public Control, IContainer
	{
	public:
		Container();
		virtual ~Container();

		virtual WString GetClassName() { return L"Container"; };
		virtual LPVOID GetInterface(LPCTSTR pstrName);

		virtual void SetAttribute(LPCTSTR key, LPCTSTR value);
		virtual void EventHandler(TEvent& event);
	};
}
#endif // _CONTAINER_H_