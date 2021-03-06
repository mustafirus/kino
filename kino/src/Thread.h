// Thread.h: interface for the Thread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREAD_H__E7D87217_272F_11D2_A6D9_204C4F4F5020__INCLUDED_)
#define AFX_THREAD_H__E7D87217_272F_11D2_A6D9_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//#define ThreadPtr __declspec( thread ) static Thread*
#define ThreadPtr __thread Thread*

class Thread
{
//	static DWORD ThreadPtrIndex; // Non microsoft implementation
	static ThreadPtr pCurentThread;
//	HANDLE	hThread;
//	DWORD	nThreadID;
protected:
	int		exit_code;
	bool	auto_delete;
	Thread(){};
//Attributes
public:
//Construction
public:
	Thread(bool suspended, bool autodel);
	virtual ~Thread();
//Operations
	virtual void Attach();
	virtual void Detach();
	virtual int Run(){return -1;};
	virtual void Resume();
//	operator HANDLE(){return hThread;};
	static Thread* GetCurrent();
private:
	static int Start(Thread* pThread);
};

#endif // !defined(AFX_THREAD_H__E7D87217_272F_11D2_A6D9_204C4F4F5020__INCLUDED_)
