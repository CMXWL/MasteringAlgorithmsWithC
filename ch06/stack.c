#include <stdlib.h>

#include "../ch01_List/list.h"
#include "stack.h"

/*
��stackָ����ջ��ѹ��һ��Ԫ�ء�
��Ԫ�ذ���һ��ָ��data��ָ�룬���ֻҪԪ����Ȼ������ջ�У�data���õ��ڴ��һֱ��Ч��
��data��صĴ洢�ռ佫�ɺ����ĵ�����������
*/
int stack_push(Stack * stack, const void * data)
{
	return list_ins_next(stack, NULL, data);
}

/*
��stackָ����ջ�е���һ��Ԫ�ء�
����ʱ��dataָ���ѵ���Ԫ���д洢�����ݡ�
��data��صĴ洢�ռ佫�ɺ����ĵ�����������
*/
int stack_pop(Stack * stack, void ** data)
{
	return list_rem_next(stack, NULL, data);
}
