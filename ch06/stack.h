#pragma once
#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#include "../ch01_List/list.h"

// Implement stack as linked lists.
typedef List Stack;

// Public interfaces
#define stack_init list_init

#define stack_destroy list_destroy

int stack_push(Stack *stack, const void* data);

int stack_pop(Stack *stack, void **data);

#define stack_peek(stack) ((stack) == NULL ? NULL : (stack)->head->data)

#define stack_size list_size
#endif // !STACK_H

