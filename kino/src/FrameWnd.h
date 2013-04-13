#if !defined(AFX_FRAMEWND_H__D4762F74_FD10_11D1_A66A_204C4F4F5020__INCLUDED_)
#define AFX_FRAMEWND_H__D4762F74_FD10_11D1_A66A_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FrameWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FrameWnd frame

class WinHandler;
class RKey;
class Table;
class FormAction;
class Frame;
class RecordSet;
class Record;
class RLink;
class FrameThread;
class MainWnd;
class DataContext;

#include "Defines.h"
#include "TabMap.h"

class FrameWnd
{
	FrameWnd*	prev;
	FrameWnd*	next;
//Members
	Frame*		pRootFrame;
	Record*		pRec;
	Record*		pRecdef;
	RLink*		pRLink;
	RFieldControls vCtrls;
	TabMap		tabmap;
	TabPos		curpos;
	bool		bAutoSave; 
public:
	FrameWnd(DataContext* pdc, FrameWnd* pPrev);
protected:
//	virtual void Init(char* str, CreateContext* pContext);
public:
//	ScreenAction*	pAction;
public:
	FrameWnd(/*ScreenAction* pa, char* str, CreateContext* pContext*/);

// Attributes
public:

// Interface
// Operations
public:
	void AdjustSize(SIZE& sz);
	char* GetControls(char* str, RFieldControls& vCtrls);
	void Action(Record* pr, RField* prf, int nID);
	virtual bool DestroyWindow();
	void SetPos(TabPos pos){curpos = pos;};


	operator Record*(){return pRec;};
	operator RecordSet*(){return (RecordSet*)pRec;};

	bool AskSave_n_Exit();
//	void Save();
//	void SetModified(){modified = true;};
//	void Show(bool show);
//	Wnd* GetWnd(){return this;};
//	Frame* GetFrame(){return pRootFrame;}

//	bool Start();
	virtual bool PreTranslateMessage(void* pMsg);
protected:

// Implementation
// Message handlers
	void OnClose();
	void OnCopy();
	void OnPaste();
	void OnDestroy();
	
// Operations
protected:
	void ShowAll(bool sa_show);
	FrameWnd* GetThreadWnd();
	MainWnd*  GetMainWnd();

//Destruction
	virtual ~FrameWnd(); // Destruct by DestroyWindow

	
//	bool OnKeyDown(uint nChar, uint nRepCnt, uint nFlags);
//	bool OnKeyUp(uint nChar, uint nRepCnt, uint nFlags);
//	bool OnLButtonDown(uint nFlags, CPoint point);
//	bool OnLButtonDblClk(uint nFlags);
//	void OnNorm(RecordSet* pRec);


public:
	void BringToTop(bool top);
	static void RegisterClass();
	virtual const char* GetClassName(){return "FRAMEWND";};

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMEWND_H__D4762F74_FD10_11D1_A66A_204C4F4F5020__INCLUDED_)
