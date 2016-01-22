
#ifndef _FACE_LAZY_H_
#define _FACE_LAZY_H_

#pragma once

namespace Face
{
	template<typename T>
	class FaceLazy : public Face::FaceObject
	{
	protected:
		class Internal
		{
		public:
			Face::FaceFunc<T()> evaluator;
			T value;
			bool evaluated;
		};

		Ptr<Internal>	_internalValue;
	public:
		FaceLazy()
		{
		}

		FaceLazy(const Face::FaceFunc<T()>& evaluator)
		{
			_internalValue = new Internal;
			_internalValue->evaluated = false;
			_internalValue->evaluator = evaluator;
		}

		FaceLazy(const T& value)
		{
			_internalValue = new Internal;
			_internalValue->evaluated = true;
			_internalValue->value = value;
		}

		FaceLazy(const FaceLazy<T>& lazy)
			:_internalValue(lazy._internalValue)
		{
		}

		FaceLazy<T>& operator=(const Face::FaceFunc<T()>& evaluator)
		{
			_internalValue = new Internal;
			_internalValue->evaluated = false;
			_internalValue->evaluator = evaluator;
			return *this;
		}

		FaceLazy<T>& operator=(const T& value)
		{
			_internalValue = new Internal;
			_internalValue->evaluated = true;
			_internalValue->value = value;
			return *this;
		}

		FaceLazy<T>& operator=(const FaceLazy<T>& lazy)
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
				_internalValue->evaluator = Face::FaceFunc<T()>();
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
