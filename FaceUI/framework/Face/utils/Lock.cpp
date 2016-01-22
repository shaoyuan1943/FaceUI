
#include "stdafx.h"
#include "Lock.h"

namespace Face
{
	FaceLock::FaceLock()
	{
		::InitializeCriticalSection(&this->cs_);
	}

	FaceLock::~FaceLock()
	{
		::LeaveCriticalSection(&this->cs_);
		::DeleteCriticalSection(&this->cs_);
	}

	void FaceLock::Enter()
	{
		::EnterCriticalSection(&this->cs_);
	}

	void FaceLock::Leave()
	{
		::LeaveCriticalSection(&this->cs_);
	}

	FaceSemaphore::FaceSemaphore(int iMaxSources/* = 5*/, int iEnableSources/* = 0*/)
	{
		hSemaphore_ = ::CreateSemaphore(nullptr, iEnableSources, iMaxSources, nullptr);
	}

	FaceSemaphore::~FaceSemaphore()
	{
		::CloseHandle(hSemaphore_);
	}

	void FaceSemaphore::Wait(unsigned long ultime/* = INFINITE*/)
	{
		::WaitForSingleObject(hSemaphore_, ultime);
	}

	void FaceSemaphore::Release(int iEnableSources/* = 1*/)
	{
		::ReleaseSemaphore(hSemaphore_, iEnableSources, nullptr);
		::CloseHandle(hSemaphore_);
	}

	FaceMutex::FaceMutex(bool bInitialOwner/* = false*/)
	{
		hMutex_ = ::CreateMutex(NULL, bInitialOwner, NULL);
	}

	FaceMutex::~FaceMutex()
	{
		::CloseHandle(hMutex_);
	}

	void FaceMutex::Wait(unsigned long ultime/* = INFINITE*/)
	{
		::WaitForSingleObject(hMutex_, ultime);
	}

	void FaceMutex::Release()
	{
		::ReleaseMutex(hMutex_);
		::CloseHandle(hMutex_);
	}
}