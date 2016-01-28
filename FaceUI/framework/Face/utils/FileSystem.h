
#ifndef _FACE_FILESYSTEM_H_
#define _FACE_FILESYSTEM_H_

#pragma once

namespace Face
{
	using namespace std;
	class FACE_API FilePath : public Object
	{
	protected:
		String	_fullPath;
		void Initialize();
	public:
		static const wchar_t Delimiter = L'\\';

		FilePath();
		FilePath(const String& _filePath);
		FilePath(const wchar_t* _filePath);
		FilePath(const FilePath& _filePath);
		~FilePath();

		static fint Compare(const FilePath& a, const FilePath& b);
		bool	 operator==(const FilePath& filePath_){ return Compare(*this, filePath_) == 0; }
		bool	 operator!=(const FilePath& filePath_){ return Compare(*this, filePath_) != 0; }
		bool	 operator< (const FilePath& filePath_){ return Compare(*this, filePath_) <  0; }
		bool	 operator<=(const FilePath& filePath_){ return Compare(*this, filePath_) <= 0; }
		bool	 operator> (const FilePath& filePath_){ return Compare(*this, filePath_) >  0; }
		bool	 operator>=(const FilePath& filePath_){ return Compare(*this, filePath_) >= 0; }
		FilePath	operator/(const WString& relativePath)const;

		bool	IsFile()const;
		bool	IsFolder()const;
		bool	IsRoot()const;
		String		GetName()const;
		FilePath	GetFolder()const;
		String		GetFullPath()const;
		String		GetRelativePathFor(const FilePath& _filePath);
	};

	class FACE_API File : public Object
	{
	private:
		FilePath	filePath_;

	public:
		File();
		File(const FilePath& _filePath);
		~File();

		const FilePath& GetFilePath()const;
		bool	Exists()const;
		bool	Delete()const;
		bool	Rename(const String& newName)const;
	};

	class FACE_API Folder : public Object
	{
	private:
		FilePath filePath_;

	public:
		Folder();
		Folder(const FilePath& _filePath);
		~Folder();

		const FilePath& GetFilePath()const;
		bool GetFolders(std::list<Folder>& folders)const;
		bool GetFiles(std::list<File>& files)const;
			
		bool Exists()const;
		bool Create(bool recursively)const;
		bool Delete(bool recursively)const;
		bool Rename(const String& newName)const;
	};
}

#endif