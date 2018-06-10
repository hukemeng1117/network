//
//  list.c
//  myC
//
//  Created by 尚立 on 2018/6/6.
//  Copyright © 2018年 尚立. All rights reserved.
//

#include "list.h"
#include <stdio.h>
#include <assert.h>

extern void* zmalloc(size_t size);
extern void zfree(void* ptr);

list *listCreate(void) {
    list* l = (list*)zmalloc(sizeof(list));
    if (!l) return NULL;
    listHead(l) = NULL;
    listTail(l) = NULL;
    listLen(l) = 0;
    l->free = NULL;
    return l;
}

void listAddNodeHead(list *list, void *value) {
    if (!list) return;
    
    listNode* pnode = (listNode*)zmalloc(sizeof(listNode));
    if (!pnode) return;
    
    pnode->value = value;
    pnode->prev = NULL;
    
    if(listLen(list) == 0) {
        pnode->next = NULL;
        list->head = pnode;
        list->tail = pnode;
    } else {
        list->head->prev = pnode;
        pnode->next = list->head;
        list->head = pnode;
    }
    list->len++;
    
    return;
}

void listAddNodeTail(list *list,void *value) {
    if (!list) return;
    
    listNode* pnode = (listNode*)zmalloc(sizeof(listNode));
    if (!pnode) return;
    pnode->value = value;
    pnode->next = NULL;
    
    if(listLen(list) == 0) {
        list->tail = list->head = pnode;
        pnode->prev = NULL;
    } else {
        list->tail->next = pnode;
        pnode->prev = list->tail;
        list->tail = pnode;
    }
    list->len++;
    
    return;
}

void listEmpty(list *list) {
    if(!list) return;
    
    listNode *current,*next;
    
    current = list->head;
    
    while(listLen(list)--) {
        next = current->next;
        if (list->free) list->free(current->value);
        zfree(current);
        current = next;
    }
    list->head = list->tail = NULL;
    list->len = 0;
    return;
}

void listClear(list* list) {
    if(!list) return;
    listEmpty(list);
    zfree(list);
    return;
}

void listInsertNode(list *list, listNode *old_node, void *value) {
    if(!list || !old_node) return;
    listNode* current = list->head;
    
    listNode* pnode = (listNode*)zmalloc(sizeof(listNode));
    if (!pnode) return;
    pnode->value = value;
    pnode->next = NULL;
    
    ulong i = 0;
    while(i < list->len) {
        if(current == old_node) {
            listNode* next = current->next;
            pnode->prev = current;
            current->next = pnode;
            pnode->next = next;
            next->prev = pnode;
            list->len ++;
            break;
        }
        current = current->next;
        i++;
    }
    return;
}

void listDelNode(list *list, listNode *node) {
    if(!list || !node) return;
    listNode* current = list->head;
    
    ulong i = 0;
    while(i < list->len) {
        if(current == node) {
            listNode* next = current->next;
            listNode* prev = current->prev;
            if(list->free) list->free(current);
            if(prev)
                prev->next = next;
            else
                list->head = next;
            
            if(next)
                next->prev = prev;
            else
                list->head = prev;
            
            list->len--;
            break;
        }
        current = current->next;
        i++;
    }
    return;
}

void listJoin(list *l, list *o) {
    if(!l || !o) return;
    
    if(l->tail)
        l->tail->next = o->head;
    else
        l->tail = o->head;
    
    if(o->head)
        o->head->prev = l->tail;
    
    l->len += o->len;
}

listNode* listIndex(list *list, long index) {
    if(!list) return NULL;
    if(index >= list->len) return NULL;
    
    listNode *n;
    if (index < 0) {
        index = (-index)-1;
        n = list->tail;
        while(index-- && n) n = n->prev;
    } else {
        n = list->head;
        while(index-- && n) n = n->next;
    }
    return n;
}




