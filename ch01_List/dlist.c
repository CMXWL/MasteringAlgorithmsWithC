#include <stdlib.h>
#include <string.h>
#include "dlist.h"

/*
初始化由参数list所指定的双向链表。
该函数必须在双向链表做其他任何操作之前调用。当调用dlist_destroy时，这里传入的destroy参数提供了一种释放动态分配空间的方法。
双向链表中如果不包含需要手动释放空间的数据，destroy参数应该设置为NULL。
*/
void dlist_init(DList * list, void(*destory)(void *data))
{
	list->size = 0;
	list->destroy = destory;
	list->head = NULL;
	list->tail = NULL;
}

/*
销毁由参数list所指定的双向链表。
*/
void destory(DList *list)
{
	void *data;

	// 移除每个元素
	while (list_size(list) > 0)
	{
		if (dlist_remove(list, dlist_tail(list), (void**)&data) == 0 && list->destroy != NULL)
		{
			list->destroy(data);
		}
	}

	memset(list, 0, sizeof(DList));
}

/*
将元素插入由list指定的双向链表中element元素之后。
当插入空链表中时，element可能指向任何位置，为了避免混淆，element此时应该设置为NULL。
新的元素包含一个指向data的指针，因此只要钙元素仍在链表中时，data所引用的内存空间就应
该保持合法。由调用者负责管理data所引用的存储空间。
*/
int dlist_ins_next(DList * list, DListElmt * element, const void * data)
{
	DListElmt *new_element;

	// eleemnt 不能为NULL，除非链表为空
	if (element == NULL && dlist_size(list) != 0)
	{
		return -1;
	}
	// 为新元素申请内存空间
	if ((new_element = (DListElmt*)malloc(sizeof(DListElmt))) == NULL)
	{
		return -1;
	}
	// 将新元素插入链表中
	new_element->data = (void*)data;

	if (dlist_size(list) == 0)
	{
		// 当链表为空时，将新元素插入链表头部
		list->head = new_element;
		list->head->prev = NULL;
		list->tail = new_element;
		list->tail->next = NULL;
	}
	else
	{
		// 当链表不为空时，将链表插入element之后
		new_element->next = element->next;
		new_element->prev = element;

		if (element->next == NULL)
		{
			list->tail = new_element;
		}
		else
		{
			element->next->prev = new_element;
		}
		element->next = new_element;
	}

	list->size++;

	return 0;
}

/*
将元素插入由list指定的双向链表中element元素之前。
当插入空链表中时，element可能指向任何位置，为了避免混淆，element此时应该设置为NULL。
新的元素包含一个指向data的指针，因此只要钙元素仍在链表中时，data所引用的内存空间就应
该保持合法。由调用者负责管理data所引用的存储空间。
*/
int dlist_ins_prev(DList * list, DListElmt * element, const void * data)
{
	DListElmt *new_element;

	if (element == NULL && dlist_size(list) != 0)
	{
		return -1;
	}
	
	if ((new_element = (DListElmt*)mallock(sizeof(DListElmt))) == NULL)
	{
		return -1;
	}

	new_element->data = data;

	if (dlist_size(list) == 0)
	{
		list->head = new_element;
		list->head->prev = NULL;
		list->tail = new_element;
		list->tail->next = NULL;
	}
	else
	{
		new_element->prev = element->prev;
		new_element->next = element;

		if (element->prev == NULL)
		{
			list->head = new_element;
		}
		else
		{
			element->prev->next = new_element;
		}
		element->prev = new_element;
	}

	list->size++;

	return 0;
}

/*
从由list指定的双向链表中移除由element所指定的元素。
函数返回后，参数data将指向已移除元素中存储的数据域。由调用者负责管理data所引用的存储空间。
*/
int dlist_remove(DList * list, DListElmt * element, void ** data)
{
	DListElmt *old_element;
	if (element == NULL || dlist_size(list) == 0)
	{
		return -1;
	}
	*data = element->data;

	if (element == list->head)
	{
		list->head = list->head->next;

		if (list->head == NULL)
		{
			list->tail = NULL;
		}
		else
		{
			list->head->prev = NULL;
		}
	}
	else
	{
		element->prev->next = element->next;
		if (element->next == NULL)
		{
			list->tail = element->prev;
		}
		else
		{
			element->next->prev = element->prev;
		}
	}

	free(element);
	list->size--;

	return 0;
}
