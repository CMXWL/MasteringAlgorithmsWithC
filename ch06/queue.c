#include <stdlib.h>

#include "../ch01_List/list.h"
#include "queue.h"

/*
��queueָ���Ķ���ĩβ����һ��Ԫ�ء�
��Ԫ�ذ���һ��ָ��data��ָ�룬���ֻҪԪ����Ȼ�����ڶ����У�data���õ��ڴ��һֱ��Ч��
��data��صĴ洢�ռ佫�ɺ����ĵ�����������
*/
int queue_enqueue(Queue * queue, void * data)
{
	return list_ins_next(queue, list_tail(queue), data);
}

/*
��queueָ���Ķ���ͷ��ɾ��һ��Ԫ�ء�
����ʱ��dataָ���ѳ���Ԫ���д洢�����ݡ�
��data��صĴ洢�ռ佫�ɺ����ĵ�����������
*/
int queue_dequeue(Queue * queue, void ** data)
{
	return list_rem_next(queue, NULL, data);
}
