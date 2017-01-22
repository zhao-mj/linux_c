#include <stdio.h>
void test(){
	int i=0,l=10;

	for(;i++<l;){
		printf("i:%d\n",i);
		if(i==5){
			goto haha;
		}
	}
haha:
	printf("fjjfafjoe\n");
}
int main(){
	test();
	return 0;
}