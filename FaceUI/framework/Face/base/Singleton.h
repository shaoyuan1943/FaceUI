
#ifndef _FACE_SINGLETON_H_
#define _FACE_SINGLETON_H_

#pragma once

namespace Face
{
	/*
		Note: 非线程安全
	*/
	template<typename T>
	class Singleton : public Face::NotCopyable
	{
	public:
		virtual void Init()
		{}

		virtual void Destory()
		{}

		static T* getInstance()
		{
			if (object_ == nullptr)
			{
				object_ = new T;
				object_->Init();
			}
			return object_;
		}
	protected:
		Singleton()
		{
		}

		~Singleton()
		{
			Destory();
			SAFE_DELETE(object_);
		}
	private:
		static T* object_;
	};

	template<typename T>
	T* Singleton<T>::object_ = nullptr;
}
#endif