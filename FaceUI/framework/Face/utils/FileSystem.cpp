#include "stdafx.h"
#include "FileSystem.h"

#pragma comment(lib, "Shlwapi.lib")

namespace Face
{
	void FilePath::Initialize()
	{
		wchar_t* buffer = new wchar_t[_fullPath.Length() + 1];
		wcscpy_s(&buffer[0], _fullPath.Length() + 1, _fullPath.Buffer());
		size_t len = wcslen(buffer);

		for (size_t i = 0; i < len; i++)
		{
			if (buffer[i] == L'\\' || buffer[i] == L'/')
			{
				buffer[i] = Delimiter;
			}
		}
		_fullPath = &buffer[0];

		if (_fullPath.Length() < 2 || _fullPath[1] != L':')
		{
			wchar_t buffer[MAX_PATH + 1] = { 0 };
			::GetCurrentDirectory(sizeof(buffer) / sizeof(*buffer), buffer);
			_fullPath = WString(buffer) + L"\\" + _fullPath;
		}
		{
			wchar_t buffer[MAX_PATH + 1] = { 0 };
			if (_fullPath.Length() == 2 && _fullPath[1] == L':')
			{
				_fullPath += L"\\";
			}
			::GetFullPathName(_fullPath.Buffer(), sizeof(buffer) / sizeof(*buffer), buffer, NULL);
			_fullPath = buffer;
		}

		if (_fullPath[_fullPath.Length() - 1] == Delimiter)
		{
			_fullPath = _fullPath.Left(_fullPath.Length() - 1);
		}
		SAFE_DELETE_ARRAY(buffer);
	}

	FilePath::FilePath()
	{
	}

	FilePath::FilePath(const WString& _filePath)
		:_fullPath(_filePath)
	{
		Initialize();
	}

	FilePath::FilePath(const wchar_t* _filePath)
		:_fullPath(_filePath)
	{
		Initialize();
	}

	FilePath::FilePath(const FilePath& _filePath)
		:_fullPath(_filePath._fullPath)
	{
		Initialize();
	}

	FilePath::~FilePath()
	{
	}

	fint FilePath::Compare(const FilePath& a, const FilePath& b)
	{
		return WString::Compare(a._fullPath, b._fullPath);
	}

	FilePath FilePath::operator/(const WString& relativePath)const
	{
		if (IsRoot())
		{
			return relativePath;
		}
		else
		{
			return _fullPath + L"/" + relativePath;
		}
	}

	bool FilePath::IsFile()const
	{
		WIN32_FILE_ATTRIBUTE_DATA info;
		BOOL result = ::GetFileAttributesEx(_fullPath.Buffer(), GetFileExInfoStandard, &info);
		if (!result) 
			return false;
		return (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
	}

	bool FilePath::IsFolder()const
	{
		WIN32_FILE_ATTRIBUTE_DATA info;
		BOOL result = GetFileAttributesEx(_fullPath.Buffer(), GetFileExInfoStandard, &info);
		if (!result) 
			return false;
		return (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
	}

	bool FilePath::IsRoot()const
	{
		return _fullPath == L"";
	}

	WString FilePath::GetName()const
	{
		WString delimiter = Delimiter;
		fint pos = _fullPath.FindLast(L'\\');
		if (!pos)
			return _fullPath;
		
		return _fullPath.Right(_fullPath.Length() - pos - 1);
	}

	FilePath FilePath::GetFolder()const
	{
		WString delimiter = Delimiter;
		fint pos = _fullPath.FindLast(L'\\');
		if (!pos)
			return FilePath();
		return _fullPath.Left(pos);
	}

	WString FilePath::GetFullPath()const
	{
		return _fullPath;
	}

	WString FilePath::GetRelativePathFor(const FilePath& _filePath)
	{
		if (_fullPath.Length()==0 || _filePath._fullPath.Length()==0 || _fullPath[0] != _filePath._fullPath[0])
		{
			return _filePath._fullPath;
		}
		wchar_t buffer[MAX_PATH + 1] = { 0 };
		PathRelativePathTo(
			buffer,
			_fullPath.Buffer(),
			(IsFolder() ? FILE_ATTRIBUTE_DIRECTORY : 0),
			_filePath._fullPath.Buffer(),
			(_filePath.IsFolder() ? FILE_ATTRIBUTE_DIRECTORY : 0)
			);
		return buffer;
	}

	File::File()
	{
	}
		
	File::File(const FilePath& _filePath)
		:filePath_(_filePath)
	{
	}

	File::~File()
	{
	}

	const FilePath& File::GetFilePath()const
	{
		return filePath_;
	}

	bool File::Exists()const
	{
		return filePath_.IsFile();
	}

	bool File::Delete()const
	{
		return DeleteFile(filePath_.GetFullPath().Buffer()) != 0;
	}

	bool File::Rename(const WString& newName)const
	{
		WString oldFileName = filePath_.GetFullPath();
		WString newFileName = (filePath_.GetFolder() / newName).GetFullPath();
		return MoveFile(oldFileName.Buffer(), newFileName.Buffer()) != 0;
	}

	Folder::Folder()
	{
	}
		
	Folder::Folder(const FilePath& _filePath)
		:filePath_(_filePath)
	{
	}

	Folder::~Folder()
	{
	}

	const FilePath& Folder::GetFilePath()const
	{
		return filePath_;
	}

	bool Folder::GetFolders(std::list<Face::Folder>& folders)const
	{
		if (!Exists()) 
			return false;
		WIN32_FIND_DATA findData;
		HANDLE findHandle = INVALID_HANDLE_VALUE;

		while (true)
		{
			if (findHandle == INVALID_HANDLE_VALUE)
			{
				WString searchPath = (filePath_ / L"*").GetFullPath();
				findHandle = FindFirstFile(searchPath.Buffer(), &findData);
				if (findHandle == INVALID_HANDLE_VALUE)
				{
					break;
				}
			}
			else
			{
				BOOL result = FindNextFile(findHandle, &findData);
				if (result == 0)
				{
					FindClose(findHandle);
					break;
				}
			}

			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (wcscmp(findData.cFileName, L".") != 0 && wcscmp(findData.cFileName, L"..") != 0)
				{
					folders.push_back(Folder(filePath_ / findData.cFileName));
				}
			}
		}
		return true;
	}

	bool Folder::GetFiles(std::list<Face::File>& files)const
	{
		if (!Exists()) 
			return false;
		WIN32_FIND_DATA findData;
		HANDLE findHandle = INVALID_HANDLE_VALUE;

		while (true)
		{
			if (findHandle == INVALID_HANDLE_VALUE)
			{
				WString searchPath = (filePath_ / L"*").GetFullPath();
				findHandle = FindFirstFile(searchPath.Buffer(), &findData);
				if (findHandle == INVALID_HANDLE_VALUE)
				{
					break;
				}
			}
			else
			{
				BOOL result = FindNextFile(findHandle, &findData);
				if (result == 0)
				{
					FindClose(findHandle);
					break;
				}
			}

			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				files.push_back(File(filePath_ / findData.cFileName));
			}
		}
		return true;
	}

	bool Folder::Exists()const
	{
		return filePath_.IsFolder();
	}

	bool Folder::Create(bool recursively)const
	{
		if (recursively)
		{
			auto folder = filePath_.GetFolder();
			if (folder.IsFile()) return false;
			if (folder.IsFolder()) return Create(false);
			return Folder(folder).Create(true) && Create(false);
		}
		else
		{
			return CreateDirectory(filePath_.GetFullPath().Buffer(), NULL) != 0;
		}
	}

	bool Folder::Delete(bool recursively)const
	{
		if (!Exists()) return false;
		if (recursively)
		{
			std::list<Folder> folders;
			GetFolders(folders);
			for (auto iter = folders.begin(); iter != folders.end(); iter++)
			{
				if (!(*iter).Delete(true))
				{
					return false;
				}
			}

			std::list<File> files;
			GetFiles(files);
			for (auto iter = files.begin(); iter != files.end(); iter++)
			{
				if (!(*iter).Delete())
				{
					return false;
				}
			}

			return Delete(false);
		}
		return RemoveDirectory(filePath_.GetFullPath().Buffer()) != 0;
	}

	bool Folder::Rename(const WString& newName)const
	{
		WString oldFileName = filePath_.GetFullPath();
		WString newFileName = (filePath_.GetFolder() / newName).GetFullPath();
		return MoveFile(oldFileName.Buffer(), newFileName.Buffer()) != 0;
	}
	
}
