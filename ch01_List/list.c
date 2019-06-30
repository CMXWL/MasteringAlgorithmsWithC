#include <stdlib.h>
#include <string.h>
#include "list.h"

/* 
��ʼ���ɲ���listָ��������
�ú�����������������������֮ǰ���á�������list_destroyʱ��destroy�����ṩ��һ���ͷŶ�̬��������ݵķ�����
���磬��������������mallock��̬��������ݣ�������������ʱ��destroyӦ������Ϊfree�����ͷ����ݡ����ڰ����ü�����̬�����Ա�Ľṹ�����ݣ�
destroyӦ������Ϊһ���û��Զ��������������ͨ����ÿһ����̬����ĳ�Ա�Լ��ṹ���������free���ͷ����ݡ�����������Ӧ���ͷŵ����ݣ�
destroyӦ������ΪNULL��
*/
void list_init(List * list, void(*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

/*
�����ɲ���listָ��������
����list_destroy���κ������Ĳ�����������ִ�У������ٴε���list_init��list_destory��������
���е�Ԫ�ض��Ƴ����������list_init����destroy��ΪNULL�����Ƴ�������ÿ��Ԫ��ʱ�����øú���һ�Ρ�
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
��listָ����������element�������һ����Ԫ�ء�
���element����ΪNULL������Ԫ�ز�������ͷ������Ԫ�ذ���һ��ִ��data��ָ�룬
���ֻҪ��Ԫ�ػ��������У�data�����õ��ڴ�ռ��Ӧ�ñ��ֺϷ�������data�����õĴ洢�ռ��ǵ����ߵ����Ρ�
*/
int list_ins_next(List * list, ListElmt * element, const void * data)
{
	ListElmt *new_element;
	// Ϊ��Ԫ�ط���洢�ռ�
	if ((new_element = (ListElmt*)malloc(sizeof(ListElmt))) == NULL)
	{
		return -1;
	}
	// ����Ԫ�ز���list��
	new_element->data = data;
	if (element == NULL)
	{
		// ��������ͷ��
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
�Ƴ���listָ����������element����Ǹ�Ԫ�ء�
���element����ΪNULL�����Ƴ�����ͷԪ�ء����÷��غ�dataָ�����Ƴ�Ԫ���д洢�����ݡ�
�ɵ������߸������data�����õĴ洢�ռ�.
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

