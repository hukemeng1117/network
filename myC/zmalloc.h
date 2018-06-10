//
//  zmalloc.h
//  myC
//
//  Created by 尚立 on 2018/6/6.
//  Copyright © 2018年 尚立. All rights reserved.
//

#ifndef zmalloc_h
#define zmalloc_h
#include <stdio.h>
void* zmalloc(size_t size);
void zfree(void* ptr);

#endif /* zmalloc_h */
