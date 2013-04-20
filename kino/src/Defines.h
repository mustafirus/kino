#if !defined(DEFINES_H_69179D70_464B_11d2_A720_204C4F4F5020_INCLUDED_)
#define DEFINES_H_69179D70_464B_11d2_A720_204C4F4F5020_INCLUDED_


#include "Set.h"

class RFieldControl;
//typedef Set<RFieldControl> RFieldControls;

class Column;
//typedef Set<Column> Columns;


typedef struct COLINFO_tag
{
	int			len;
	int			offset;
	int			type;
	int			intr;
	char		name[32];
}COLINFO, *PCOLINFO;

typedef struct TABLEINFO_tag
{
	int			cols;
	int			size;
	COLINFO*	pColInfo;	
}TABLEINFO, *PTABLEINFO;

#endif // !defined(DEFINES_H_69179D70_464B_11d2_A720_204C4F4F5020_INCLUDED_)
