#include <stdlib.h>
#include <string.h>
#include "clist.h"

void clist_init(CList * list, void(*destory)(void *data))
{
}

void clist_destroy(CList * list)
{
}

int clist_ins_next(CList * list, CListElmt * element, const void * data)
{
	return 0;
}

int clist_rem_next(CList * list, CListElmt * element, void ** data)
{
	return 0;
}
