#include <stdlib.h>

#include "../ch01_List/list.h"
#include "stack.h"

/*
向stack指定的栈中压入一个元素。
新元素包含一个指向data的指针，因此只要元素仍然存在于栈中，data引用的内存就一直有效。
与data相关的存储空间将由函数的调用者来管理。
*/
int stack_push(Stack * stack, const void * data)
{
	return list_ins_next(stack, NULL, data);
}

/*
从stack指定的栈中弹出一个元素。
返回时，data指向已弹出元素中存储的数据。
与data相关的存储空间将由函数的调用者来管理。
*/
int stack_pop(Stack * stack, void ** data)
{
	return list_rem_next(stack, NULL, data);
}
