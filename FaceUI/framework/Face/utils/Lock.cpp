
#include "stdafx.h"
#include "Lock.h"

namespace Face
{
	Lock::Lock()
	{
		::InitializeCriticalSection(&this->cs_);
	}

	Lock::~Lock()
	{
		::LeaveCriticalSection(&this->cs_);
		::DeleteCriticalSection(&this->cs_);
	}

	void Lock::Enter()
	{
		::EnterCriticalSection(&this->cs_);
	}

	void Lock::Leave()
	{
		::LeaveCriticalSection(&this->cs_);
	}

	Semaphore::Semaphore(int iMaxSources/* = 5*/, int iEnableSources/* = 0*/)
	{
		hSemaphore_ = ::CreateSemaphore(nullptr, iEnableSources, iMaxSources, nullptr);
	}

	Semaphore::~Semaphore()
	{
		::CloseHandle(hSemaphore_);
	}

	void Semaphore::Wait(unsigned long ultime/* = INFINITE*/)
	{
		::WaitForSingleObject(hSemaphore_, ultime);
	}

	void Semaphore::Release(int iEnableSources/* = 1*/)
	{
		::ReleaseSemaphore(hSemaphore_, iEnableSources, nullptr);
		::CloseHandle(hSemaphore_);
	}

	Mutex::Mutex(bool bInitialOwner/* = false*/)
	{
		hMutex_ = ::CreateMutex(NULL, bInitialOwner, NULL);
	}

	Mutex::~Mutex()
	{
		::CloseHandle(hMutex_);
	}

	void Mutex::Wait(unsigned long ultime/* = INFINITE*/)
	{
		::WaitForSingleObject(hMutex_, ultime);
	}

	void Mutex::Release()
	{
		::ReleaseMutex(hMutex_);
		::CloseHandle(hMutex_);
	}
}