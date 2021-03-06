// RField.cpp: implementation of the RField class.
//
//////////////////////////////////////////////////////////////////////

#include "stdx.h"
#include "Dict.h"
#include "RKey.h"
#include "Database.h"
#include "Record.h"
#include "RField.h"

RField::RField() :
buf(NULL), type(Field::Char), pQField(NULL), pPRField(NULL), pRec(NULL), pind(NULL),
/*state(s_dummy), */buf_attrib(b_none), /*attr(Hidden), */v(0){}

RField::RField(QField* pqf, Record* pr, RField* prf) :
buf(NULL), type(Field::Char), pQField(pqf), pPRField(prf), pRec(pr), pind(NULL),
/*state(s_dummy), */buf_attrib(b_none), /*attr(Hidden), */v(0)
{
	if(!prf)
	{
		buf		= new char[GetLen()];
		pind	= Record::pDB->GetIndicator(1);
		*buf	= 0;
		buf_attrib = b_native;
	}else
	{
		buf		= NULL;
		buf_attrib = b_foreign;
	}
}

RField::~RField()
{
	if(buf_attrib == b_native && buf)
		delete[] buf;
	if(pind)
		delete pind;
}

RField::operator const char*()
{
	if(state == s_null)
		return NULL;
	if(state != s_data)
		pRec->Load();
	return buf;
}

void RField::SetData(bool null)
{
	v++;
	state = s_data;
	if(null)
		state = s_null;
	else
		state /= s_null;
	state /= s_modified;
	if(state != s_null)
	{
		if(type != Field::Char)
			type = Record::pDB->Convert(buf, buf, type, Field::Char);
		if(((Field*)*pQField)->deft)
		{
			if(!strncmp(buf, ((Field*)*pQField)->deft, strlen(buf)))
				state = s_null;
		}
	}
};

void RField::SetDefault()
{
	Field* pf = *pQField;
	if(pf->deft)
	{
		strcpy(buf, pf->deft);
		state = s_modified;
	}
}

int RField::GetLen()
{
	return ((Field*)*pQField)->strlen+1;
}

bool RField::ro()
{
	return pQField->ro() || !((QTable*)*pQField)->IsMaster();
};

RField::operator RKey*()
{
	return pRec->GetRKey(*pQField);
}

void RField::Delete()
{
	if(ro())
	{
		RKey* prk = pRec->GetRKey(*this);
		state = s_modified;
		state = s_null;
		v++;
		pRec->SetModified();
		prk->SetNull();
		pRec->Refresh(prk);
	}else
	{
		state = s_null;
		state = s_modified;
		state = s_data;
		v++;
	}
}
