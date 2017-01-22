#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void test(char **data){
    char* p;
    char* a="54321";
    p = malloc(strlen(a)-1);
    memcpy(p,a,strlen(a));
    printf("sizeof:%d\n",sizeof(a));

    *data = p;
    
}
typedef struct
{
    int a;
    int b;
}yac_shared_segment;

static int create_segments(yac_shared_segment **p){
    yac_shared_segment t;
    *p = (yac_shared_segment *)malloc(10);
    t.a = 1;
    t.b = 2;
    *p = &t;
    printf("p:%x\n",p);
    printf("*p:%x\n",*p);
    printf("**p:%d\n",(**p).b);
}
void main(){
    char *d;
    yac_shared_segment *p=NULL;
    printf("--p:%x--\n",p);
    printf("--&p:%x--\n",&p);
    create_segments(&p);
    //printf("p.a:%d\n",p);

    printf("--p1:%x--\n",p);
    printf("--&p1:%x--\n",&p);

    printf("--p.a:%d--\n",(*p).a);
}