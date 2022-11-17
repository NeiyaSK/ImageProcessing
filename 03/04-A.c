// 課題No04-A
#include<stdio.h>
void wasa (int *wa, int *sa, int x, int y);

int main(void){
    int x, y, wa, sa;
    scanf("%d", &x);
    scanf("%d", &y);
    wa=&x;
    sa=&y;
    printf("x = %d, y = %d\n", x,y);
    //wasa(x,y);   // 適切な引数の指定をする
    printf("wa = x+y = %d\nsa = x-y = %d\n", wa, sa);
    return 0;
}
/*
void wasa(int x,int y){
    int sum =x+y;
    (*wa) = sum;
    int def =x-y;
    (*sa) = def;
    return;
}
*/