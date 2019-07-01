#include <stdlib.h>

#include "../ch01_List/list.h"
#include "queue.h"

/*
向queue指定的队列末尾插入一个元素。
新元素包含一个指向data的指针，因此只要元素仍然存在于队列中，data引用的内存就一直有效。
与data相关的存储空间将由函数的调用者来管理。
*/
int queue_enqueue(Queue * queue, void * data)
{
	return list_ins_next(queue, list_tail(queue), data);
}

/*
从queue指定的队列头部删除一个元素。
返回时，data指向已出队元素中存储的数据。
与data相关的存储空间将由函数的调用者来管理。
*/
int queue_dequeue(Queue * queue, void ** data)
{
	return list_rem_next(queue, NULL, data);
}
