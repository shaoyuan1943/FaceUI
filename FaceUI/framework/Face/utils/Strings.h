
#ifndef _FACE_STRING_H_
#define _FACE_STRING_H_

#pragma once

namespace Face
{
	using namespace Face;

	class FACE_API FaceString : public Face::FaceObject
	{
	private:
		static const wchar_t zero = 0;
		mutable wchar_t* buffer_;
		mutable volatile fint* counter_;
		mutable fint start_;
		mutable fint length_;
		mutable fint realLength_;

		static fint CalculateLength(const wchar_t* buffer_)
		{
			fint result = 0;
			while (*buffer_++)
				result++;
			return result;
		}

		static fint Compare(const wchar_t* bufA, const FaceString& strB)
		{
			const wchar_t* bufB = strB.buffer_ + strB.start_;
			const wchar_t* bufAOld = bufA;
			fint length_ = strB.length_;
			while (length_-- && *bufA)
			{
				fint diff = *bufA++ - *bufB++;
				if (diff != 0)
				{
					return diff;
				}
			};
			return CalculateLength(bufAOld) - strB.length_;
		}

	public:

		static fint Compare(const FaceString& strA, const FaceString& strB)
		{
			const wchar_t* bufA = strA.buffer_ + strA.start_;
			const wchar_t* bufB = strB.buffer_ + strB.start_;
			fint length_ = strA.length_ < strB.length_ ? strA.length_ : strB.length_;
			while (length_--)
			{
				fint diff = *bufA++ - *bufB++;
				if (diff != 0)
				{
					return diff;
				}
			};
			return strA.length_ - strB.length_;
		}

	private:

		void Inc()const
		{
			if (counter_)
			{
				INCRC(counter_);
			}
		}

		void Dec()const
		{
			if (counter_)
			{
				if (DECRC(counter_) == 0)
				{
					delete[] buffer_;
					delete counter_;
				}
			}
		}

		FaceString(const FaceString& string, fint _start, fint _length)
		{
			if (_length <= 0)
			{
				buffer_ = (wchar_t*)&zero;
				counter_ = 0;
				start_ = 0;
				length_ = 0;
				realLength_ = 0;
			}
			else
			{
				buffer_ = string.buffer_;
				counter_ = string.counter_;
				start_ = string.start_ + _start;
				length_ = _length;
				realLength_ = string.realLength_;
				Inc();
			}
		}

		FaceString(const FaceString& dest, const FaceString& source, fint index, fint count)
		{
			if (index == 0 && count == dest.length_ && source.length_ == 0)
			{
				buffer_ = (wchar_t*)&zero;
				counter_ = 0;
				start_ = 0;
				length_ = 0;
				realLength_ = 0;
			}
			else
			{
				counter_ = new fint(1);
				start_ = 0;
				length_ = dest.length_ - count + source.length_;
				realLength_ = length_;
				buffer_ = new wchar_t[length_ + 1];
				memcpy(buffer_, dest.buffer_ + dest.start_, sizeof(wchar_t)*index);
				memcpy(buffer_ + index, source.buffer_ + source.start_, sizeof(wchar_t)*source.length_);
				memcpy(buffer_ + index + source.length_, (dest.buffer_ + dest.start_ + index + count), sizeof(wchar_t)*(dest.length_ - index - count));
				buffer_[length_] = 0;
			}
		}
	public:
		static FaceString Empty;

		FaceString()
		{
			buffer_ = (wchar_t*)&zero;
			counter_ = 0;
			start_ = 0;
			length_ = 0;
			realLength_ = 0;
		}

		FaceString(const wchar_t& _char)
		{
			counter_ = new fint(1);
			start_ = 0;
			length_ = 1;
			buffer_ = new wchar_t[2];
			buffer_[0] = _char;
			buffer_[1] = 0;
			realLength_ = length_;
		}

		FaceString(const wchar_t* _buffer, fint _length)
		{
			if (_length <= 0)
			{
				buffer_ = (wchar_t*)&zero;
				counter_ = 0;
				start_ = 0;
				length_ = 0;
				realLength_ = 0;
			}
			else
			{
				buffer_ = new wchar_t[_length + 1];
				memcpy(buffer_, _buffer, _length*sizeof(wchar_t));
				buffer_[_length] = 0;
				counter_ = new fint(1);
				start_ = 0;
				length_ = _length;
				realLength_ = _length;
			}
		}

		FaceString(const wchar_t* _buffer, bool copy = true)
		{
			CHECK_ERROR(_buffer != 0, L"FaceString::FaceString(const wchar_t*, bool)#Cannot construct a string from nullptr.");
			if (copy)
			{
				counter_ = new fint(1);
				start_ = 0;
				length_ = CalculateLength(_buffer);
				buffer_ = new wchar_t[length_ + 1];
				memcpy(buffer_, _buffer, sizeof(wchar_t)*(length_ + 1));
				realLength_ = length_;
			}
			else
			{
				buffer_ = (wchar_t*)_buffer;
				counter_ = 0;
				start_ = 0;
				length_ = CalculateLength(_buffer);
				realLength_ = length_;
			}
		}

		FaceString(const FaceString& string)
		{
			buffer_ = string.buffer_;
			counter_ = string.counter_;
			start_ = string.start_;
			length_ = string.length_;
			realLength_ = string.realLength_;
			Inc();
		}

		FaceString(FaceString&& string)
		{
			buffer_ = string.buffer_;
			counter_ = string.counter_;
			start_ = string.start_;
			length_ = string.length_;
			realLength_ = string.realLength_;

			string.buffer_ = (wchar_t*)&zero;
			string.counter_ = 0;
			string.start_ = 0;
			string.length_ = 0;
			string.realLength_ = 0;
		}

		~FaceString()
		{
			Dec();
		}

		const wchar_t* Buffer()const
		{
			if (start_ + length_ != realLength_)
			{
				wchar_t* newBuffer = new wchar_t[length_ + 1];
				memcpy(newBuffer, buffer_ + start_, sizeof(wchar_t)*length_);
				newBuffer[length_] = 0;
				Dec();
				buffer_ = newBuffer;
				counter_ = new fint(1);
				start_ = 0;
				realLength_ = length_;
			}
			return buffer_ + start_;
		}

		FaceString& operator=(const FaceString& string)
		{
			if (this != &string)
			{
				Dec();
				buffer_ = string.buffer_;
				counter_ = string.counter_;
				start_ = string.start_;
				length_ = string.length_;
				realLength_ = string.realLength_;
				Inc();
			}
			return *this;
		}

		FaceString& operator=(FaceString&& string)
		{
			if (this != &string)
			{
				Dec();
				buffer_ = string.buffer_;
				counter_ = string.counter_;
				start_ = string.start_;
				length_ = string.length_;
				realLength_ = string.realLength_;

				string.buffer_ = (wchar_t*)&zero;
				string.counter_ = 0;
				string.start_ = 0;
				string.length_ = 0;
				string.realLength_ = 0;
			}
			return *this;
		}

		FaceString& operator+=(const FaceString& string)
		{
			return *this = *this + string;
		}

		FaceString operator+(const FaceString& string)const
		{
			return FaceString(*this, string, length_, 0);
		}

		bool operator==(const FaceString& string)const
		{
			return Compare(*this, string) == 0;
		}

		bool operator!=(const FaceString& string)const
		{
			return Compare(*this, string) != 0;
		}

		bool operator>(const FaceString& string)const
		{
			return Compare(*this, string) > 0;
		}

		bool operator>=(const FaceString& string)const
		{
			return Compare(*this, string) >= 0;
		}

		bool operator<(const FaceString& string)const
		{
			return Compare(*this, string) < 0;
		}

		bool operator<=(const FaceString& string)const
		{
			return Compare(*this, string) <= 0;
		}

		bool operator==(const wchar_t* buffer_)const
		{
			return Compare(buffer_, *this) == 0;
		}

		bool operator!=(const wchar_t* buffer_)const
		{
			return Compare(buffer_, *this) != 0;
		}

		bool operator>(const wchar_t* buffer_)const
		{
			return Compare(buffer_, *this) < 0;
		}

		bool operator>=(const wchar_t* buffer_)const
		{
			return Compare(buffer_, *this) <= 0;
		}

		bool operator<(const wchar_t* buffer_)const
		{
			return Compare(buffer_, *this)>0;
		}

		bool operator<=(const wchar_t* buffer_)const
		{
			return Compare(buffer_, *this) >= 0;
		}

		wchar_t operator[](fint index)const
		{
			CHECK_ERROR(index >= 0 && index < length_, L"FaceString:<wchar_t>:operator[](fint)#Argument index not in range.");
			return buffer_[start_ + index];
		}

		fint Length()const
		{
			return length_;
		}

		fint IndexOf(wchar_t c)const
		{
			const wchar_t* reading = buffer_ + start_;
			for (fint i = 0; i < length_; i++)
			{
				if (reading[i] == c)
					return i;
			}
			return -1;
		}

		FaceString Left(fint count)const
		{
			CHECK_ERROR(count >= 0 && count <= length_, L"FaceString::Left(fint)#Argument count not in range.");
			return FaceString(*this, 0, count);
		}

		FaceString Right(fint count)const
		{
			CHECK_ERROR(count >= 0 && count <= length_, L"FaceString::Right(fint)#Argument count not in range.");
			return FaceString(*this, length_ - count, count);
		}

		FaceString Sub(fint index, fint count)const
		{
			CHECK_ERROR(index >= 0 && index <= length_, L"FaceString::Sub(fint, fint)#Argument index not in range.");
			CHECK_ERROR(index + count >= 0 && index + count <= length_, L"FaceString::Sub(fint, fint)#Argument count not in range.");
			return FaceString(*this, index, count);
		}

		FaceString Remove(fint index, fint count)const
		{
			CHECK_ERROR(index >= 0 && index < length_, L"FaceString::Remove(fint, fint)#Argument index not in range.");
			CHECK_ERROR(index + count >= 0 && index + count <= length_, L"FaceString::Remove(fint, fint)#Argument count not in range.");
			return FaceString(*this, FaceString(), index, count);
		}

		FaceString Insert(fint index, const FaceString& string)const
		{
			CHECK_ERROR(index >= 0 && index <= length_, L"FaceString::Insert(fint)#Argument count not in range.");
			return FaceString(*this, string, index, 0);
		}

		fint ToInt()const
		{
			wchar_t* endptr = 0;
			fint result = wcstol(this->Buffer(), &endptr, 10);
			return result;
		}

		void Lower()
		{
			_wcslwr_s((wchar_t*)this->Buffer(), this->Length() + 1);
		}

		void Upper()
		{
			_wcsupr_s((wchar_t*)this->Buffer(), this->Length() + 1);
		}

		fint Find(const wchar_t c) const
		{
			if (c == '\0')
				return -1;
			wchar_t* ptr = wcsrchr(buffer_, c);
			if (ptr)
			{
				return (fint)(ptr - buffer_);
			}
			return -1;
		}

		fint Find(const wchar_t* sub) const
		{
			if (sub == nullptr)
				return -1;
			wchar_t* ptr = wcsstr(buffer_, sub);
			if (sub == nullptr)
				return -1;
			return (fint)(ptr - buffer_);
		}

		fint FindLast(const wchar_t c) const
		{
			if (c == '\0')
				return -1;
			
			for (fint i = this->Length() - 1; i > 0; i--)
			{
				if (buffer_[i] == c)
					return i;
			}
			return -1;
		}

		fint FindFirst(const wchar_t c) const
		{
			if (c == '\0')
				return -1;

			for (fint i = 0; i < this->Length(); i++)
			{
				if (buffer_[i] == c)
					return i;
			}
			return -1;
		}

		friend bool operator<(const wchar_t* left, const FaceString& right)
		{
			return Compare(left, right)<0;
		}

		friend bool operator<=(const wchar_t* left, const FaceString& right)
		{
			return Compare(left, right) <= 0;
		}

		friend bool operator>(const wchar_t* left, const FaceString& right)
		{
			return Compare(left, right) > 0;
		}

		friend bool operator>=(const wchar_t* left, const FaceString& right)
		{
			return Compare(left, right) >= 0;
		}

		friend bool operator==(const wchar_t* left, const FaceString& right)
		{
			return Compare(left, right) == 0;
		}

		friend bool operator!=(const wchar_t* left, const FaceString& right)
		{
			return Compare(left, right) != 0;
		}

		friend FaceString operator+(const wchar_t* left, const FaceString& right)
		{
			return FaceString(left, false) + right;
		}

		static std::wstring A2W(const char* lsz)
		{
			int codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;
			fint iLength = strlen(lsz);
			fint iCharCount = ::MultiByteToWideChar(codepage, 0, lsz, iLength, nullptr, 0);

			wchar_t* pW = new wchar_t[iCharCount + 1];
			ZeroMemory(pW, (iCharCount + 1) * sizeof(wchar_t));

			::MultiByteToWideChar(codepage, 0, lsz, iLength, (LPWSTR)(pW), iCharCount);
			std::wstring wstr(pW);

			delete[] pW;

			return wstr;
		}

		static std::string W2A(const wchar_t* lwsz)
		{
			fint iLength = wcslen(lwsz);
			fint codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;
			fint iCharCount = ::WideCharToMultiByte(codepage, 0, lwsz, iLength, nullptr, 0, nullptr, nullptr);

			char* pA = new char[iCharCount + 1];
			ZeroMemory(pA, (iCharCount + 1)* sizeof(char));

			::WideCharToMultiByte(codepage, 0, lwsz, iLength, pA, iCharCount, nullptr, nullptr);
			std::string str(pA);

			delete[] pA;

			return str;
		}

		static std::string W2U(const wchar_t* lwsz)
		{
			fint iLength = wcslen(lwsz);
			fint iCharCount = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)(lwsz), iLength, nullptr, 0, nullptr, nullptr);

			char* pA = new char[iCharCount + 1];
			ZeroMemory(pA, (iCharCount + 1) * sizeof(char));

			::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)(lwsz), iLength, pA, iCharCount, nullptr, nullptr);
			std::string str(pA);

			delete[] pA;

			return str;
		}

		static std::wstring U2W(const char*lsz)
		{
			fint iLength = strlen(lsz);
			fint iCharCount = ::MultiByteToWideChar(CP_UTF8, 0, lsz, iLength, nullptr, 0);
			
			wchar_t* pW = new wchar_t[iCharCount + 1];
			ZeroMemory(pW, (iCharCount + 1) * sizeof(wchar_t));
			
			::MultiByteToWideChar(CP_UTF8, 0, lsz, iLength, (LPWSTR)(pW), iCharCount);
			std::wstring wstr(pW);
			
			delete[] pW;
			
			return wstr;
		}
	};

	typedef Face::FaceString WString;
}

#endif
