#include <stdlib.h>
#include <string.h>
#include "dlist.h"

/*
��ʼ���ɲ���list��ָ����˫������
�ú���������˫�������������κβ���֮ǰ���á�������dlist_destroyʱ�����ﴫ���destroy�����ṩ��һ���ͷŶ�̬����ռ�ķ�����
˫�������������������Ҫ�ֶ��ͷſռ�����ݣ�destroy����Ӧ������ΪNULL��
*/
void dlist_init(DList * list, void(*destory)(void *data))
{
	list->size = 0;
	list->destroy = destory;
	list->head = NULL;
	list->tail = NULL;
}

/*
�����ɲ���list��ָ����˫������
*/
void destory(DList *list)
{
	void *data;

	// �Ƴ�ÿ��Ԫ��
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
��Ԫ�ز�����listָ����˫��������elementԪ��֮��
�������������ʱ��element����ָ���κ�λ�ã�Ϊ�˱��������element��ʱӦ������ΪNULL��
�µ�Ԫ�ذ���һ��ָ��data��ָ�룬���ֻҪ��Ԫ������������ʱ��data�����õ��ڴ�ռ��Ӧ
�ñ��ֺϷ����ɵ����߸������data�����õĴ洢�ռ䡣
*/
int dlist_ins_next(DList * list, DListElmt * element, const void * data)
{
	DListElmt *new_element;

	// eleemnt ����ΪNULL����������Ϊ��
	if (element == NULL && dlist_size(list) != 0)
	{
		return -1;
	}
	// Ϊ��Ԫ�������ڴ�ռ�
	if ((new_element = (DListElmt*)malloc(sizeof(DListElmt))) == NULL)
	{
		return -1;
	}
	// ����Ԫ�ز���������
	new_element->data = (void*)data;

	if (dlist_size(list) == 0)
	{
		// ������Ϊ��ʱ������Ԫ�ز�������ͷ��
		list->head = new_element;
		list->head->prev = NULL;
		list->tail = new_element;
		list->tail->next = NULL;
	}
	else
	{
		// ������Ϊ��ʱ�����������element֮��
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
��Ԫ�ز�����listָ����˫��������elementԪ��֮ǰ��
�������������ʱ��element����ָ���κ�λ�ã�Ϊ�˱��������element��ʱӦ������ΪNULL��
�µ�Ԫ�ذ���һ��ָ��data��ָ�룬���ֻҪ��Ԫ������������ʱ��data�����õ��ڴ�ռ��Ӧ
�ñ��ֺϷ����ɵ����߸������data�����õĴ洢�ռ䡣
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
����listָ����˫���������Ƴ���element��ָ����Ԫ�ء�
�������غ󣬲���data��ָ�����Ƴ�Ԫ���д洢���������ɵ����߸������data�����õĴ洢�ռ䡣
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
