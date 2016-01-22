
#ifndef _FACE_POINTER_H_
#define _FACE_POINTER_H_

#pragma once

namespace Face
{
	template<typename T>
	class Ptr
	{
		template<typename X>
		friend class Ptr;
	protected:
		typedef void(*Destructor)(volatile fint*, void*);

		volatile fint*		_counter;
		T*					_reference;
		void*				_originalReference;
		Destructor			_originalDestructor;

		void Inc()
		{
			if (_counter)
			{
				INCRC(_counter);
			}
		}

		void Dec()
		{
			if (_counter)
			{
				if (DECRC(_counter) == 0)
				{
					_originalDestructor(_counter, _originalReference);
					_counter = 0;
					_reference = 0;
					_originalReference = 0;
					_originalDestructor = 0;
				}
			}
		}

		volatile fint* Counter()const
		{
			return _counter;
		}

		Ptr(volatile fint* _counter, T* _reference, void* _originalReference, Destructor _originalDestructor)
			:_counter(_counter)
			, _reference(_reference)
			, _originalReference(_originalReference)
			, _originalDestructor(_originalDestructor)
		{
			Inc();
		}
	public:

		Ptr()
			:_counter(0)
			, _reference(0)
			, _originalReference(0)
			, _originalDestructor(0)
		{
		}

		Ptr(T* pointer)
			:_counter(0)
			, _reference(0)
			, _originalReference(0)
			, _originalDestructor(0)
		{
			if (pointer)
			{
				_counter = Face::ReferenceCounterOperator<T>::CreateCounter(pointer);
				_reference = pointer;
				_originalReference = pointer;
				_originalDestructor = &Face::ReferenceCounterOperator<T>::DeleteReference;
				Inc();
			}
		}

		Ptr(const Ptr<T>& pointer)
			:_counter(pointer._counter)
			, _reference(pointer._reference)
			, _originalReference(pointer._originalReference)
			, _originalDestructor(pointer._originalDestructor)
		{
			Inc();
		}

		Ptr(Ptr<T>&& pointer)
			:_counter(pointer._counter)
			, _reference(pointer._reference)
			, _originalReference(pointer._originalReference)
			, _originalDestructor(pointer._originalDestructor)
		{
			pointer._counter = 0;
			pointer._reference = 0;
			pointer._originalReference = 0;
			pointer._originalDestructor = 0;
		}

		template<typename C>
		Ptr(const Ptr<C>& pointer)
			:_counter(0)
			, _reference(0)
			, _originalReference(0)
			, _originalDestructor(0)
		{
			T* converted = pointer.Obj();
			if (converted)
			{
				_counter = pointer.Counter();
				_reference = converted;
				_originalReference = pointer._originalReference;
				_originalDestructor = pointer._originalDestructor;
				Inc();
			}
		}

		~Ptr()
		{
			Dec();
		}

		template<typename C>
		Ptr<C> Cast()const
		{
			C* converted = dynamic_cast<C*>(_reference);
			return Ptr<C>((converted ? _counter : 0), converted, _originalReference, _originalDestructor);
		}

		Ptr<T>& operator=(T* pointer)
		{
			Dec();
			if (pointer)
			{
				_counter = Face::ReferenceCounterOperator<T>::CreateCounter(pointer);
				_reference = pointer;
				_originalReference = pointer;
				_originalDestructor = &Face::ReferenceCounterOperator<T>::DeleteReference;
				Inc();
			}
			else
			{
				_counter = 0;
				_reference = 0;
				_originalReference = 0;
				_originalDestructor = 0;
			}
			return *this;
		}

		Ptr<T>& operator=(const Ptr<T>& pointer)
		{
			if (this != &pointer)
			{
				Dec();
				_counter = pointer._counter;
				_reference = pointer._reference;
				_originalReference = pointer._originalReference;
				_originalDestructor = pointer._originalDestructor;
				Inc();
			}
			return *this;
		}

		Ptr<T>& operator=(Ptr<T>&& pointer)
		{
			if (this != &pointer)
			{
				Dec();
				_counter = pointer._counter;
				_reference = pointer._reference;
				_originalReference = pointer._originalReference;
				_originalDestructor = pointer._originalDestructor;

				pointer._counter = 0;
				pointer._reference = 0;
				pointer._originalReference = 0;
				pointer._originalDestructor = 0;
			}
			return *this;
		}

		template<typename C>
		Ptr<T>& operator=(const Ptr<C>& pointer)
		{
			T* converted = pointer.Obj();
			Dec();
			if (converted)
			{
				_counter = pointer._counter;
				_reference = converted;
				_originalReference = pointer._originalReference;
				_originalDestructor = pointer._originalDestructor;
				Inc();
			}
			else
			{
				_counter = 0;
				_reference = 0;
				_originalReference = 0;
				_originalDestructor = 0;
			}
			return *this;
		}

		bool operator==(const T* pointer)const
		{
			return _reference == pointer;
		}

		bool operator!=(const T* pointer)const
		{
			return _reference != pointer;
		}

		bool operator>(const T* pointer)const
		{
			return _reference > pointer;
		}

		bool operator>=(const T* pointer)const
		{
			return _reference >= pointer;
		}

		bool operator<(const T* pointer)const
		{
			return _reference < pointer;
		}

		bool operator<=(const T* pointer)const
		{
			return _reference <= pointer;
		}

		bool operator==(const Ptr<T>& pointer)const
		{
			return _reference == pointer._reference;
		}

		bool operator!=(const Ptr<T>& pointer)const
		{
			return _reference != pointer._reference;
		}

		bool operator>(const Ptr<T>& pointer)const
		{
			return _reference > pointer._reference;
		}

		bool operator>=(const Ptr<T>& pointer)const
		{
			return _reference >= pointer._reference;
		}

		bool operator<(const Ptr<T>& pointer)const
		{
			return _reference < pointer._reference;
		}

		bool operator<=(const Ptr<T>& pointer)const
		{
			return _reference <= pointer._reference;
		}

		operator bool()const
		{
			return _reference != 0;
		}

		T* Obj()const
		{
			return _reference;
		}

		T* operator->()const
		{
			return _reference;
		}
	};
}
#endif