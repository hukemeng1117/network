#include "list.h"
#include "zmalloc.h"

#define INITMAPLEN 16

typedef struct mapNode{
	void* key;
	void* value;
	struct mapNode* next;
}mapNode;

typedef struct map
{
 	unsigned long len;
 	unsigned long useNum;
 	mapNode** talble;
 	unsigned long (*hashKey)(void* key);
 	int (*comapreKey)(void* key,void* key2);
 	void* (*copyKey)(void* key);
 	void* (*copyValue)(void* value);
}map;

unsigned long hashKey(void* key) {
	unsigned int hash = 1315423911; 
	unsigned int i  = key; 

	for(i = 0; i < len; str++, i++) 
	{ 
		hash ^= ((hash << 5) + (*str) + (hash >> 2)); 
	} 

	return hash; 
}

int comapreKey(void* key,void* key2){
	if(key == key2) {
		return 1;
	}
	return 0;
}

void* copyKey(void* key) {
	return key;
}

void* copyValue(void* value) {
	return value;
}

static inline mapInit(map* m) {
	m->hashKey = hashKey;
	m->comapreKey = comapreKey;
}

map* mapCreate(){
	map* m = (map*)zmalloc(sizeof(map));
	if(!m) return NULL;

	memset(m,0,sizeof(map));
	m->len = INITMAPLEN;
	mapInit(m);
}


