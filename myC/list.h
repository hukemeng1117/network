//
//  list.h
//  myC
//
//  Created by 尚立 on 2018/6/6.
//  Copyright © 2018年 尚立. All rights reserved.
//

#ifndef _LIST_H_
#define _LIST_H_

typedef unsigned long ulong;

typedef struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *value;
} listNode;

typedef struct list {
    listNode *head;
    listNode *tail;
    void (*free)(void *value);
    ulong len;
} list;

#define listLen(l) (l->len)
#define listTail(l) (l->tail)
#define listHead(l) (l->head)

list *listCreate(void);
void listAddNodeHead(list *list, void *value);
void listAddNodeTail(list *list,void *value);
void listEmpty(list *list) ;
void listClear(list* list) ;
void listInsertNode(list *list, listNode *old_node, void *value);
void listDelNode(list *list, listNode *node);
void listJoin(list *l, list *o) ;
listNode* listIndex(list *list, long index);


#endif
