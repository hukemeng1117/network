//
//  main.c
//  myC
//
//  Created by 尚立 on 2018/6/6.
//  Copyright © 2018年 尚立. All rights reserved.
//

#include <stdio.h>
#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>

void test1() {
    
    list* l = listCreate();
    list* o = listCreate();
    int i = 0;
    for(;i<256;i++) {
        listAddNodeTail(l,(void*)i);
    }
    assert(256 == listLen(l));
    
    for(i=0;i<256;i++) {
        listAddNodeTail(o,(void*)(i*2));
    }
    assert(256 == listLen(o));
    
    listJoin(l,o);
    
    assert(512 == listLen(l));
    
    for(i=0;i<256;i++) {
        listNode* node = l->head;
        assert(i == node->value);
        listDelNode(l,node);
    }
    
    for(i=0;i<256;i++) {
        listNode* node = l->head;
        assert(i*2 == (int)node->value);
        listDelNode(l,node);
    }
    
    assert(0 == listLen(l));
    listClear(l);
}

void test2() {
    list* l = listCreate();
    int i = 0;
    for(;i<256;i++) {
        listAddNodeTail(l,(void*)i);
    }
    assert(256 == listLen(l));
    
    listNode* node = listIndex(l,100);
    assert(100 == node->value);
    listDelNode(l,node);
    
    node = listIndex(l,99);
    assert(99 == node->value);
    node = node->next;
    assert(101 == node->value);
    node = node->prev;
    assert(99 == node->value);
    
    listInsertNode(l,node,100);
    node = node->next;
    assert(100 == node->value);
    node = node->next;
    assert(101 == node->value);
    node = node->prev;
    assert(100 == node->value);
    
    listEmpty(l);
    assert(0 == listLen(l));
    listClear(l);
}

int getlocalip(char* outip)
{
    int i=0;
    int sockfd;
    struct ifconf ifconf;
    char buf[512];
    struct ifreq *ifreq;
    char* ip;
    //初始化ifconf
    ifconf.ifc_len = 512;
    ifconf.ifc_buf = buf;
    
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
    {
        return -1;
    }
    ioctl(sockfd, SIOCGIFCONF, &ifconf);    //获取所有接口信息
    close(sockfd);
    //接下来一个一个的获取IP地址
    ifreq = (struct ifreq*)buf;
    for(i=(ifconf.ifc_len/sizeof(struct ifreq)); i>0; i--)
    {
        char* data = &(&(ifreq->ifr_addr))->sa_data;
        for(int j = 0;j<14;j++) {
            printf("%d  ",*(data+j));
        }
        printf("\n");
        ip = inet_ntoa(((struct sockaddr_in*)&(ifreq->ifr_addr))->sin_addr);
        
        if(strcmp(ip,"127.0.0.1")==0)  //排除127.0.0.1，继续下一个
        {
            ifreq++;
            continue;
        }
        strcpy(outip,ip);
        return 0;
    }
    
    return -1;
}

int main(int argc, char const *argv[])
{
    test1();
    test2();
    char *ip = (char*)malloc(64);
    if(-1 != getlocalip(ip)) {
        printf("%s",ip);
    }
}
