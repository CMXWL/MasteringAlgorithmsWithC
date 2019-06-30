#include <stdlib.h>
#include <string.h>
#include "clist.h"

/*
用来初始化由参数list所指定的循环链表。
*/
void clist_init(CList * list, void(*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
}

/*
销毁由参数list所指定的循环链表。
*/
void clist_destroy(CList * list)
{
	void *data;
	while (clist_size(list) > 0)
	{
		if (clist_rem_next(list, NULL, (void**)&data) == 0 && list->destroy != NULL)
		{
			list->destroy(data);
		}
	}

	memset(list, 0, sizeof(CList));
}

/*
将元素插入由list所指定的循环链表中element之后。
*/
int clist_ins_next(CList * list, CListElmt * element, const void * data)
{
	CListElmt *new_element;

	if (element == NULL && clist_size(list) != 0)
	{
		return -1;
	}

	if ((new_element = (CListElmt*)malloc(sizeof(CListElmt))) == NULL)
	{
		return -1;
	}

	new_element->data = data;

	if (clist_size(list) == 0)
	{
		list->head = new_element;
		list->head->next = new_element;
	}
	else
	{
		new_element->next = element->next;
		element->next = new_element;
	}

	list->size++;

	return 0;
}

/*
移除由参数list指定的循环链表中element后面的元素。
*/
int clist_rem_next(CList * list, CListElmt * element, void ** data)
{
	CListElmt *old_element;
	
	if (clist_size(list) == 0)
	{
		return -1;
	}

	*data = element->next->data;

	if (element->next == element)
	{
		old_element = element;
		list->head = NULL;
	}
	else
	{
		old_element = element->next;
		element->next = element->next->next;
		if (old_element == clist_head(list))
		{
			list->head = old_element->next;
		}
	}

	free(old_element);
	list->size--;

	return 0;
}
