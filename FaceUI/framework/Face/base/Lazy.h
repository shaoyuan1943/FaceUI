
#ifndef _FACE_LAZY_H_
#define _FACE_LAZY_H_

#pragma once

namespace Face
{
	template<typename T>
	class Lazy : public Object
	{
	protected:
		class Internal
		{
		public:
			Face::Func<T()> evaluator;
			T value;
			bool evaluated;
		};

		Ptr<Internal>	_internalValue;
	public:
		Lazy()
		{
		}

		Lazy(const Face::Func<T()>& evaluator)
		{
			_internalValue = new Internal;
			_internalValue->evaluated = false;
			_internalValue->evaluator = evaluator;
		}

		Lazy(const T& value)
		{
			_internalValue = new Internal;
			_internalValue->evaluated = true;
			_internalValue->value = value;
		}

		Lazy(const Lazy<T>& lazy)
			:_internalValue(lazy._internalValue)
		{
		}

		Lazy<T>& operator=(const Face::Func<T()>& evaluator)
		{
			_internalValue = new Internal;
			_internalValue->evaluated = false;
			_internalValue->evaluator = evaluator;
			return *this;
		}

		Lazy<T>& operator=(const T& value)
		{
			_internalValue = new Internal;
			_internalValue->evaluated = true;
			_internalValue->value = value;
			return *this;
		}

		Lazy<T>& operator=(const Lazy<T>& lazy)
		{
			_internalValue = lazy._internalValue;
			return *this;
		}

		const T& Value()const
		{
			if (!_internalValue->evaluated)
			{
				_internalValue->evaluated = true;
				_internalValue->value = _internalValue->evaluator();
				_internalValue->evaluator = Face::Func<T()>();
			}
			return _internalValue->value;
		}

		const bool IsEvaluated()const
		{
			return _internalValue->evaluated;
		}

		const bool IsAvailable()const
		{
			return _internalValue;
		}
	};
}

#endif
