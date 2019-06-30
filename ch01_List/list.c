#include <stdlib.h>
#include <string.h>
#include "list.h"

/* 
初始化由参数list指定的链表。
该函数必须在链表做其他操作之前调用。当调用list_destroy时，destroy参数提供了一种释放动态分配的数据的方法。
例如，如果链表包含采用mallock动态分配的数据，挡脸裱褙销毁时，destroy应该设置为free用来释放数据。对于包含好几个动态分配成员的结构化数据，
destroy应该设置为一个用户自定义的析构函数，通过对每一个动态分配的成员以及结构体自身调用free来释放数据。如果链表包含应该释放的数据，
destroy应该设置为NULL。
*/
void list_init(List * list, void(*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

/*
销毁由参数list指定的链表。
调用list_destroy后任何其他的操作都不允许执行，除非再次调用list_init。list_destory将链表中
所有的元素都移除，如果传给list_init参数destroy不为NULL，则移除链表中每个元素时都调用该函数一次。
*/
void list_destroy(List * list)
{
	void *data;

	// Remove each element.
	while (list_size(list) > 0)
	{
		if (list_rem_next(list, NULL, (void**)&data) == 0 && list->destroy != NULL)
		{
			// Call user-defined function to free dynamically allocated data.
			list->destroy(data);
		}
	}

	memset(list, 0, sizeof(List));
}

/*
在list指定的链表中element后面插入一个新元素。
如果element设置为NULL，则新元素插入链表头部。新元素包含一个执行data的指针，
因此只要钙元素还在链表中，data所引用的内存空间就应该保持合法。管理data所引用的存储空间是调用者的责任。
*/
int list_ins_next(List * list, ListElmt * element, const void * data)
{
	ListElmt *new_element;
	// 为新元素分配存储空间
	if ((new_element = (ListElmt*)malloc(sizeof(ListElmt))) == NULL)
	{
		return -1;
	}
	// 将新元素插入list中
	new_element->data = data;
	if (element == NULL)
	{
		// 插入链表头部
		if (list_size(list) == 0)
		{
			list->tail == new_element;
		}
		new_element->next = NULL;
		list->head = new_element;
	}
	else
	{
		if (element->next == NULL)
		{
			list->tail = new_element;
		}
		new_element->next = element->next;
		element->next = new_element;
	}
	list->size++;

	return 0;
}

/*
移除由list指定的链表中element后的那个元素。
如果element设置为NULL，则移除链表头元素。调用返回后，data指向已移除元素中存储的数据。
由调用智者负责管理data所引用的存储空间.
*/
int list_rem_next(List * list, ListElmt * element, void ** data)
{
	ListElmt *old_element;

	if (list_size(list) == 0)
	{
		return -1;
	}

	/* Remove the element from the list. */
	if (element == NULL)
	{
		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;

		if (list_size(list) == 1)
		{
			list->tail = NULL;
		}
	}
	else
	{
		if (element->next == NULL)
		{
			return -1;
		}
		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;

		if (list_size(list) == 0)
		{
			list->tail = element;
		}
	}
	free(old_element);
	list->size--;

	return 0;
}

