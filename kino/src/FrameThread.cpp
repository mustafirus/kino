// FrameThread.cpp: implementation of the FrameThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdx.h"
#include "FrameWnd.h"
#include "Record.h"
#include "Thread.h"
#include "Exception.h"
#include "FrameThread.h"

#define GetApp() Application::GetApp()
FrameThread::FrameThread(FrameThread*& pHead) :
next(pHead), pprev(&pHead),
Thread(true, true), pMainWnd(NULL), pRec(NULL)
{
	if(pHead)
		pHead->pprev = &next;
	pHead = this;
}

FrameThread::FrameThread(const char* tab, FrameThread*& pHead) :
next(pHead), pprev(&pHead),
Thread(true, true), pMainWnd(NULL), pRec(NULL)
{
	try{
	dc.Create(tab);
	}catch(Exception* e)
	{
//		e->SetDelMem(this);
		throw e;
	}
	if(pHead)
		pHead->pprev = &next;
	pHead = this;
	Resume();
}

FrameThread::~FrameThread()
{
	*pprev = next; 
	if(next)
		next->pprev = pprev;
	auto_delete = false;
	ifdel(pRec);
}

FrameThread* FrameThread::CreateThread()
{
	return new FrameThread(*pprev);
}

void FrameThread::CreateThread(RKey* prk, uint formID)
{
	FrameThread* ptr = new FrameThread(*pprev);
	pRec = new Record(prk);
	prk = pRec->GetRKey();
	pRec->Load();
	ptr->dc.Create(prk, NULL, formID);
	ptr->Resume();
}

bool FrameThread::InitInstance()
{
/*	int c = 30;
	while(!dc.szForm && c--)
		Sleep(100);
*///	pMainWnd = new FrameWnd(&dc, NULL);
	return true;
}

bool FrameThread::PreTranslateMessage(void* pMsg){
	return true;
};

/*FrameThread::FrameThread(RKey* prk, FrameThread*& pHead) :
next(pHead), pprev(&pHead),
WinThread(false, true), pMainWnd(NULL), pRec(NULL)
{
	dc.Create(prk);
	if(pHead)
		pHead->pprev = &next;
	pHead = this;
}
*/
