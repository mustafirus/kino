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
next(NULL), prev(pPrev), hWndTracking(NULL), pRootFrame(NULL), /*pLastFocused(NULL),*/
curpos(TabMap::first_pos), hAccel(NULL), hMenu(NULL)
{
	if(prev)
		prev->next = this;
	if(next)
		next->prev = this;
	pdc->pWnd = this;
	bAutoSave = pdc->bAutoSave; 
	GetMainWnd()->CreateChildFrame(this, pdc->szFrameName, MDIS_ALLCHILDSTYLES, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, (LPARAM)pdc);
}

void FrameWnd::AdjustSize(SIZE& sz)
{
	POINT pt = {-defspace.left, -defspace.top};
	sz.cx += defspace.left + defspace.right;
	sz.cy += defspace.top + defspace.bottom;
	Rect r(pt,sz);
	AdjustWindowRect(r, GetStyle(), FALSE);
	sz = r;
	RECT mc;
	GetClientRect(*(GetMainWnd()), &mc);
	sz.cx = min(sz.cx, mc.right - 20);
	sz.cy = min(sz.cy, mc.bottom - 20);
}

FrameWnd::~FrameWnd()
{
	if(hMenu)
		DestroyMenu(hMenu);
	if(hAccel)
		DestroyAcceleratorTable(hAccel);
	if(prev)
		prev->next = next; 
	if(next)
		next->prev = prev;
	ifdel(pRec);
	ifdel(pRootFrame);
}


void FrameWnd::OnCopy()
{

}

void FrameWnd::OnPaste()
{

}



bool FrameWnd::OnCreate(LPCREATESTRUCT lpcs)
{
	MDICREATESTRUCT* pmcs = (MDICREATESTRUCT*)lpcs->lpCreateParams;
	DataContext* pdc = (DataContext*)pmcs->lParam;
	ASSERT(pdc->szForm);
	char* str = pdc->szForm;
	ASSERT(str);
	try{
	pRootFrame = Frame::CreateFrame(str, pdc);
	}catch(Exception* e)
	{
		pdc->FreeContext();
		e->printf(MSG_ERROR_FRAME_SYNTAX_ERROR);
		e->Effect();
		return false;
	}
	if(!pRootFrame)
	{
		Exception::ex.printf(MSG_ERROR_FRAME_SYNTAX_ERROR);
		Exception::ex.Effect();
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
		_RPT0(_CRT_WARN, "On Create FrameWnd RecordSet alredy loaded !");
	}

	MINMAX mm;
	pRootFrame->GetMinMax(&mm);
	TabPos pos;

	_ASSERTE(_CrtCheckMemory());
	pRootFrame->SetTabs(&tabmap, TabMap::first_pos, pos);
	_ASSERTE(_CrtCheckMemory());
	
	POINT pt = {defspace.left, defspace.top};
	AdjustSize(mm.szDes);
	SetWindowPos(*this, NULL, 0,0, mm.szDes.cx, mm.szDes.cy, SWP_NOMOVE|
		SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOREDRAW|SWP_NOSENDCHANGING|
		SWP_NOOWNERZORDER);

//	SetCursorPos(lpcs->x + (lpcs->cx)/3, lpcs->y + (lpcs->cy)/2 );


	EnableWindow(*prev, FALSE);
//	SetFocus();
	LRESULT l = Default();
	return true;
}



void FrameWnd::OnClose() 
{
	Wait w;
	if(pRec && pRec->IsModified())
	{
		if(bAutoSave)
			pRec->Save();
		else
		{
			switch(MessageBox(*this, "��������� ���������?", "Kino", MB_YESNOCANCEL|MB_ICONQUESTION))
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

char* FrameWnd::GetControls(char* str, RFieldControls& vct)
{
	ASSERT(pRec);
	RFields rf;
	str = pRec->GetRFields(str, rf);
	for(int i = 0; i < rf.GetCount(); i++)
	{
		vct.Add(vCtrls.Add(new RFieldControl(rf[i], this, vCtrls.GetCount())));
	}
	return str;
}

void FrameWnd::OnCommands(uint nID)
{
	Wait w;
	switch(nID)
	{
	case ID_RECORD_SAVE:
		if(pRec)
			pRec->Save();
		InvalidateRect(NULL);
		break;
	case ID_RECORD_REFRESH:
		if(pRec)
			pRec->Load();
		InvalidateRect(NULL);
		return;
	case ID_RECORD_UNDO:
		if(pRec)
			pRec->Undo();
		InvalidateRect(NULL);
		return;
	};
	Action::GetAction()->Exec(this, (pRec ? pRec : pRecdef), NULL, nID);
};


FrameWnd* FrameWnd::GetThreadWnd()
{
	return ((FrameThread*)Thread::GetCurrent())->GetThreadWnd();
}
