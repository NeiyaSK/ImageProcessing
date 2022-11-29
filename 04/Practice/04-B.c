#include<stdio.h>

void my_swap(int *a, int *b);

int main (void){
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);
    printf("a=%d, b=%d\n",a,b);
    my_swap(&a,&b);
    printf("a=%d, b=%d\n",a,b);
    return 0;
}

void my_swap(int *a2, int *b2){
    int x = *a2;
    *a2 = *b2;
    *b2 = x;
}