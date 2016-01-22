
#ifndef _FACE_FILESYSTEM_H_
#define _FACE_FILESYSTEM_H_

#pragma once

namespace Face
{
	using namespace std;
	class FACE_API FaceFilePath : public FaceObject
	{
	protected:
		FaceString	_fullPath;
		void Initialize();
	public:
		static const wchar_t Delimiter = L'\\';

		FaceFilePath();
		FaceFilePath(const FaceString& _filePath);
		FaceFilePath(const wchar_t* _filePath);
		FaceFilePath(const FaceFilePath& _filePath);
		~FaceFilePath();

		static fint Compare(const FaceFilePath& a, const FaceFilePath& b);
		bool	 operator==(const FaceFilePath& filePath_){ return Compare(*this, filePath_) == 0; }
		bool	 operator!=(const FaceFilePath& filePath_){ return Compare(*this, filePath_) != 0; }
		bool	 operator< (const FaceFilePath& filePath_){ return Compare(*this, filePath_) <  0; }
		bool	 operator<=(const FaceFilePath& filePath_){ return Compare(*this, filePath_) <= 0; }
		bool	 operator> (const FaceFilePath& filePath_){ return Compare(*this, filePath_) >  0; }
		bool	 operator>=(const FaceFilePath& filePath_){ return Compare(*this, filePath_) >= 0; }
		FaceFilePath	operator/(const FaceString& relativePath)const;

		bool	IsFile()const;
		bool	IsFolder()const;
		bool	IsRoot()const;
		FaceString		GetName()const;
		FaceFilePath	GetFolder()const;
		FaceString		GetFullPath()const;
		FaceString		GetRelativePathFor(const FaceFilePath& _filePath);
	};

	class FACE_API FaceFile : public FaceObject
	{
	private:
		FaceFilePath	filePath_;

	public:
		FaceFile();
		FaceFile(const FaceFilePath& _filePath);
		~FaceFile();

		const FaceFilePath& GetFilePath()const;
		bool	Exists()const;
		bool	Delete()const;
		bool	Rename(const FaceString& newName)const;
	};

	class FACE_API FaceFolder : public FaceObject
	{
	private:
		FaceFilePath filePath_;

	public:
		FaceFolder();
		FaceFolder(const FaceFilePath& _filePath);
		~FaceFolder();

		const FaceFilePath& GetFilePath()const;
		bool GetFolders(std::list<FaceFolder>& folders)const;
		bool GetFiles(std::list<FaceFile>& files)const;
			
		bool Exists()const;
		bool Create(bool recursively)const;
		bool Delete(bool recursively)const;
		bool Rename(const FaceString& newName)const;
	};
}

#endif