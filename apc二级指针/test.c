#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
typedef struct slot_t slot_t;
typedef struct apc_cache_t apc_cache_t;
struct slot_t {
    char *key;
    char *value;
    slot_t* next;
};
struct apc_cache_t {
    void* shmaddr;
    slot_t** slots;
    int num_slots;
};


slot_t* make_slot(char *key, char* value, slot_t* slot)
{
    slot_t* p;
    p = (void *)malloc(sizeof(slot_t));
    printf("p:%x\n",p);
    if (!p) return NULL;
    p->key = key;
    p->value = value;
    p->next = slot;
    return p;
}

void apc_cache_insert(apc_cache_t* cache,char *key,char *value)
{
    slot_t** slot;
    
    slot = &cache->slots[1];
    printf("[begin]cache->slots[1]:%x,slot:%x *slot:%x \n",cache->slots[1],slot,*slot);
    while(*slot){
        printf("key:%s value:%s\n",(*slot)->key,(*slot)->value);
        slot = &(*slot)->next;
        printf("w-slot:%x\n",slot);
    }
    *slot = make_slot(key,value,*slot);
     printf("[end]slot:%x *slot:%x **slot:%x\n",slot,*slot,**slot);
}
int main(){
    int num_slots=10;
    apc_cache_t* cache;
    int cache_size;
    cache = malloc(sizeof(apc_cache_t));
    cache_size = num_slots*sizeof(slot_t*);
    
    cache->shmaddr = malloc(cache_size);
    memset(cache->shmaddr, 0, cache_size);
    
    cache->slots = (slot_t**) (((char*) cache->shmaddr));
    cache->num_slots=1;
    printf("shmaddr:%x\n",cache->shmaddr);
    printf("cache slot:%x\n",cache->slots);
    //printf("slots:%x\n",cache);
    
    apc_cache_insert(cache,"23","2323");
    apc_cache_insert(cache,"aa","bbb");
    
    apc_cache_insert(cache,"tt","hhhh");
    return 0;
}