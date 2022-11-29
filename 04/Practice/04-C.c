#include<stdio.h>

void scanf_d(int *a);

int main(void){
    int x;
    scanf_d(&x);
    printf("a=%d\n", x);
    return 0;
}

void scanf_d(int *a){
    int x2;
    scanf("%d",&x2);
    *a = x2;
}