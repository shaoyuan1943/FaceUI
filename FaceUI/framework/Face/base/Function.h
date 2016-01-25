
#ifndef _FACE_FUNCTION_H_
#define _FACE_FUNCTION_H_

#pragma once

namespace Face
{
	template<typename T>
	class Func
	{
	};

	template<typename R, typename ...TArgs>
	class Invoker : public Object
	{
	public:
		virtual R Invoke(TArgs&& ...args) = 0;
	};

	// 静态函数调用
	template<typename R, typename ...TArgs>
	class StaticInvoker : public Invoker<R, TArgs...>
	{
	protected:
		R(*function)(TArgs ...args);

	public:
		StaticInvoker(R(*_function)(TArgs...))
			:function(_function)
		{
		}

		R Invoke(TArgs&& ...args)override
		{
			return function(ForwardValue<TArgs>(args)...);
		}
	};

	// 类成员函数调用
	template<typename C, typename R, typename ...TArgs>
	class MemberInvoker : public Invoker<R, TArgs...>
	{
	protected:
		C* sender;
		R(C::*function)(TArgs ...args);

	public:
		MemberInvoker(C* _sender, R(C::*_function)(TArgs ...args))
			:sender(_sender)
			, function(_function)
		{
		}

		R Invoke(TArgs&& ...args)override
		{
			return (sender->*function)(ForwardValue<TArgs>(args)...);
		}
	};

	/*
		// 有返回值的类 () 操作符重载调用
		class A
		{
		public:
			int operator()(int i);
		};

		A a;
		int i = 0;
		Func<int(int)> func(&a, &A::operator());
		int j = func(i);
	*/
	template<typename C, typename R, typename ...TArgs>
	class ObjectInvoker : public Invoker<R, TArgs...>
	{
	protected:
		C function;

	public:
		ObjectInvoker(const C& _function)
			:function(_function)
		{
		}

		R Invoke(TArgs&& ...args)override
		{
			return function(ForwardValue<TArgs>(args)...);
		}
	};


	/*
		// 无返回值的类 () 操作符重载调用
		class A
		{
		public:
			void operator()(int i);
		};

		A a;
		int i = 0;
		Func<void(int)> func(&a, &A::operator());
		func(i);
	*/
	template<typename C, typename ...TArgs>
	class ObjectInvoker<C, void, TArgs...> : public Invoker<void, TArgs...>
	{
	protected:
		C function;

	public:
		ObjectInvoker(const C& _function)
			:function(_function)
		{
		}

		void Invoke(TArgs&& ...args)override
		{
			function(ForwardValue<TArgs>(args)...);
		}
	};


	template<typename R, typename ...TArgs>
	class Func<R(TArgs...)> : public Face::Object
	{
	protected:
		Ptr<Invoker<R, TArgs...>> invoker;
	public:
		typedef R FunctionType(TArgs...);
		typedef R ResultType;

		Func()
		{
		}

		Func(const Func<R(TArgs...)>& function)
		{
			invoker = function.invoker;
		}

		Func(R(*function)(TArgs...))
		{
			invoker = new StaticInvoker<R, TArgs...>(function);
		}

		template<typename C>
		Func(C* sender, R(C::*function)(TArgs...))
		{
			invoker = new MemberInvoker<C, R, TArgs...>(sender, function);
		}

		template<typename C>
		Func(const C& function)
		{
			invoker = new ObjectInvoker<C, R, TArgs...>(function);
		}

		R operator()(TArgs ...args)const
		{
			return invoker->Invoke(ForwardValue<TArgs>(args)...);
		}

		bool operator==(const Func<R(TArgs...)>& function)const
		{
			return invoker == function.invoker;
		}

		bool operator!=(const Func<R(TArgs...)>& function)const
		{
			return invoker != function.invoker;
		}

		operator bool()const
		{
			return invoker;
		}
	};

	template<typename R, typename C, typename ...TArgs>
	typename Func<R(TArgs...)> ToMemberFunction(C* sender, R(C::*function)(TArgs...))
	{
		return Func<R(TArgs...)>(sender, function);
	}

	template<typename R, typename ...TArgs>
	typename Func<R(TArgs...)> ToFunction(R(*function)(TArgs...))
	{
		return function;
	}

#define FUNCTION Face::ToFunction
#define MEMBER_FUNCTION Face::ToMemberFunction

	template<typename T>
	struct Binding
	{
	};

	template<typename R, typename T0, typename ...TArgs>
	struct Binding<R(T0, TArgs...)>
	{
		typedef R FunctionType(T0, TArgs...);
		typedef R CurriedType(TArgs...);
		typedef T0 FirstParameterType;

		class Binder : public Object
		{
		protected:
			Func<FunctionType> target;
			T0 firstArgument;
		public:
			Binder(const Func<FunctionType>& _target, T0 _firstArgument)
				:target(_target)
				, firstArgument(ForwardValue<T0>(_firstArgument))
			{
			}

			R operator()(TArgs ...args)const
			{
				return target(firstArgument, args...);
			}
		};

		class Currier : public Object
		{
		protected:
			Func<FunctionType>		target;
		public:
			Currier(const Func<FunctionType>& _target)
				:target(_target)
			{
			}

			Func<CurriedType> operator()(T0 firstArgument)const
			{
				return Binder(target, firstArgument);
			}
		};
	};
	

	/*
		// 函数参数拆分，形成一个新的函数
		void func1(int i);
		void func2(int i, int j);
		void func3(int i, int j, int k);
		auto f1 = Curry(func1)(1);
		f1();
		auto f2 = Curry(f1)(3);
		f2();
		auto f3 = Curry(f2)(4);
		f3(); // --> Func3(1, 2, 3)
	*/
	template<typename T>
	Func<Func<typename Binding<T>::CurriedType>(typename Binding<T>::FirstParameterType)>
		Curry(T* function)
	{
		return typename Binding<T>::Currier(function);
	}

	template<typename T>
	Func<Func<typename Binding<T>::CurriedType>(typename Binding<T>::FirstParameterType)>
		Curry(const Func<T>& function)
	{
		return typename Binding<T>::Currier(function);
	}
}
#endif