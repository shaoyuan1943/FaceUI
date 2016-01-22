
#ifndef _FACE_TEMPLATE_H_
#define _FACE_TEMPLATE_H_

namespace Face
{
	// type traits
	template<typename T>
	struct RemoveReference
	{
		typedef T	Type;
	};

	template<typename T>
	struct RemoveReference<T&>
	{
		typedef T	Type;
	};

	template<typename T>
	struct RemoveReference<T&&>
	{
		typedef T	Type;
	};

	template<typename T>
	struct RemoveConst
	{
		typedef T	Type;
	};

	template<typename T>
	struct RemoveConst<const T>
	{
		typedef T	Type;
	};

	template<typename T>
	typename RemoveReference<T>::Type&& MoveValue(T&& value)
	{
		return (typename RemoveReference<T>::Type&&)value;
	}

	template<typename T>
	T&& ForwardValue(typename RemoveReference<T>::Type&& value)
	{
		return (T&&)value;
	}

	template<typename T>
	T&& ForwardValue(typename RemoveReference<T>::Type& value)
	{
		return (T&&)value;
	}

	template<typename T>
	struct ReferenceCounterOperator
	{
		static inline volatile fint* CreateCounter(T* reference)
		{
			return new fint(0);
		}

		static inline void DeleteReference(volatile fint* counter, void* reference)
		{
			delete counter;
			delete (T*)reference;
		}
	};

	// interface
	template<typename T>
	class FaceInterface : public Face::FaceObject
	{
	public:
		virtual ~FaceInterface();
	};
}

#endif