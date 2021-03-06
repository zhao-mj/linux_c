#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "shm_com.h"
typedef struct block_t block_t;
struct block_t {
    size_t size;
    size_t prev_size;
    size_t fnext;
    size_t fprev;
};
#define BLOCKAT(offset) ((block_t*)((char *)shmaddr + offset))
int main()
{
    int running = 1;
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_stuff;
    int shmid;
    void *shmaddr;
    block_t     *first;
    key_t key=IPC_PRIVATE;
    srand((unsigned int)getpid());
    //shmid = shmget(key,sizeof(struct shared_use_st),0666 | IPC_CREAT);
    shmid =  shmget((key_t)1234,sizeof(struct shared_use_st),0666 | IPC_CREAT);
    if(shmid == -1){
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }   

    shared_memory = shmat(shmid,(void *)0,0);

    if(shared_memory == (void *)-1){
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }   
    shmaddr = shared_memory;
    printf("Memory attached at %X\n",shared_memory);
    
    shared_stuff = (struct shared_use_st *)shared_memory;
    first = BLOCKAT(4);
    printf("new:%d\n",first);
    while(running) 
    {   
        if (shared_stuff->written_by_you) 
        {   
            printf("You wrote: %s", shared_stuff->some_text);
            sleep( rand() % 4 );
            shared_stuff->written_by_you = 0;
            if(strncmp(shared_stuff->some_text,"end",3)==0){
                running = 0;
            }   
        }   
    }   


    if (shmdt(shared_memory) == -1)
    {
        printf("shmdt failed\n");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        printf("shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);

    return 0;
}