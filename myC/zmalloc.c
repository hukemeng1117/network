//
//  zmalloc.c
//  myC
//
//  Created by 尚立 on 2018/6/6.
//  Copyright © 2018年 尚立. All rights reserved.
//

#include "zmalloc.h"
#include <stdlib.h>
#include <stdio.h>

#define zmalloc_error(size) fprintf(stderr, "zmalloc: Out of memory trying to allocate %zu bytes\n",size);

void* zmalloc(size_t size) {
    void* ptr = malloc(size);
    if(!ptr) zmalloc_error(size);
    
    return ptr;
}

void zfree(void* ptr) {
    if (ptr == NULL) return;
    free(ptr);
}
