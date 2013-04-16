// Thread.cpp: implementation of the Thread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdx.h"
#include "Thread.h"

void Thread::Resume(){
	//ResumeThread(hThread);
};

/*	// Non microsoft implementation
DWORD Thread::ThreadPtrIndex = -1; */

	// Microsoft implementation
ThreadPtr Thread::pCurentThread = NULL;

void Thread::Attach()
{
/*	// Non microsoft implementation
	if(ThreadPtrIndex == -1)		
		ThreadPtrIndex = TlsAlloc();
	ASSERT(TlsGetValue(ThreadPtrIndex) == NULL);
	TlsSetValue(ThreadPtrIndex, this); */
	// Microsoft implementation
	pCurentThread = this;

	//hThread	= ::GetCurrentThread();
	//nThreadID = ::GetCurrentThreadId();
}

void Thread::Detach(){
	pCurentThread = NULL;
}

Thread* Thread::GetCurrent(){
	return pCurentThread;
}

Thread::Thread(bool suspended, bool autodel) : auto_delete(autodel)
{
	//hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Start, this,
		//suspended ? CREATE_SUSPENDED : 0, &nThreadID);
};

int Thread::Start(Thread* pThread)
{
	pThread->pCurentThread = pThread;
	int exc = pThread->exit_code = pThread->Run();
	if(pThread->auto_delete)
		delete pThread;
	return exc;
}

Thread::~Thread()
{
	if(pCurentThread != this)
	{
		DWORD status;
//		GetExitCodeThread(hThread, &status);
//		if(status == STILL_ACTIVE)
//			TerminateThread(hThread, -1);
	}
//	CloseHandle(hThread);
};
