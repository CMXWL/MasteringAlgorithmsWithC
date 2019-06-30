#pragma once
#ifndef CLIST_H
#define CLIST_H

// Define a structure for circle-linked list elements.
typedef struct CListElmt_
{
	void *data;
	struct CListElmt_ *next;
} CListElmt;

// Define a structure for circle-linked lists.
typedef struct CList_
{
	int size;
	int(*match)(const void *key1, const void *key2);
	void(*destroy)(void *data);
	CListElmt *head;
} CList;

// Public interfaces
void clist_init(CList *list, void(*destory)(void *data));
void clist_destroy(CList *list);
int clist_ins_next(CList *list, CListElmt *element, const void *data);
int clist_rem_next(CList *list, CListElmt *element, void **data);

#define clist_size(list) ((list)->size)
#define clist_head(list) ((list)->head)
#define clist_data(element) ((element)->data)
#define clist_next(element) ((element)->next)

#endif // !CLIST_H
