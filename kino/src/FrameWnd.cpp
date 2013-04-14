// FrameWnd.cpp : implementation file
//

#include "stdx.h"
#include "dblib.h"
#include "FrameThread.h"
#include "ErrorCodes.h"
#include "Action.h"
#include "Exception.h"
#include "FrameWnd.h"

//#include "Grid.h"
//#include "RFieldControl.h"


#define MAXACCELS	10
#define BASECLASS MDIChild

// For new functionality
void FrameWnd::Action(Record* pr, RField* prf, int nID)
{
	Action::GetAction()->Exec(this, pr, prf, nID);
}

FrameWnd::FrameWnd(DataContext* pdc, FrameWnd* pPrev) :
next(NULL), prev(pPrev), /*pLastFocused(NULL),*/
curpos(TabMap::first_pos)
{
	if(prev)
		prev->next = this;
	if(next)
		next->prev = this;
	pdc->pWnd = this;
	bAutoSave = pdc->bAutoSave; 
}

void FrameWnd::AdjustSize(SIZE& sz){
}

FrameWnd::~FrameWnd()
{
	if(prev)
		prev->next = next; 
	if(next)
		next->prev = prev;
	ifdel(pRec);
}


void FrameWnd::OnCopy()
{

}

void FrameWnd::OnPaste()
{

}



bool FrameWnd::OnCreate(DataContext* pdc){
	ASSERT(pdc->szForm);
	char* str = pdc->szForm;
	ASSERT(str);
	try{
	//pRootFrame = Frame::CreateFrame(str, pdc);
	}catch(Exception* e)
	{
		pdc->FreeContext();
		e->printf(MSG_ERROR_FRAME_SYNTAX_ERROR);
		e->Effect();
		return false;
	}

	pRec = pdc->GetRecord(false);//not create
	if(!pRec)
		pRecdef = pdc->GetDefRecord();//not create
	pdc->FreeContext();
	if(pRec && pRec->IsDummy())
	{
		if(!pRec->Load())
			return false;
	}else
	{
//		_RPT0(_CRT_WARN, "On Create FrameWnd RecordSet alredy loaded !");
	}

	return true;
}



void FrameWnd::OnClose() 
{
	if(pRec && pRec->IsModified())
	{
		if(bAutoSave)
			pRec->Save();
		else
		{
			int z = 0; // MessageBox(*this, "��������� ���������?", "Kino", MB_YESNOCANCEL|MB_ICONQUESTION)
#define IDYES 1
#define IDCANCEL 2
			switch(z)
			{
			case IDYES:
				pRec->Save();
				break;
			case IDCANCEL:
				return;
			}
		}
	}
	DestroyWindow();
	return;
}

bool FrameWnd::DestroyWindow()
{
	return true;
};


void FrameWnd::OnDestroy()
{
	if(next)
		next->DestroyWindow();
}

char* FrameWnd::GetControls(char* str)
{
	ASSERT(pRec);
	RFields rf;
	str = pRec->GetRFields(str, rf);
	for(int i = 0; i < rf.GetCount(); i++)
	{
		///add fild controls
	}
	return str;
}


FrameWnd* FrameWnd::GetThreadWnd()
{
	return ((FrameThread*)Thread::GetCurrent())->GetThreadWnd();
}
