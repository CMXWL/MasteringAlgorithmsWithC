#pragma once

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#include "../ch01_List/list.h"

// Implement queue as linked lists.
typedef List Queue;

// Public interfaces
#define queue_init list_init

#define queue_destroy list_destroy

int queue_enqueue(Queue *queue, void *data);

int queue_dequeue(Queue *queue, void **data);

#define queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)

#define queue_size(queue) list_size

#endif // !QUEUE_H

