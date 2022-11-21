#include<stdio.h>

void wasa(int *wa, int *sa, int x, int y);  // プロトタイプ宣言

int main(void){
    int x, y, wa, sa;
    scanf("%d", &x);
    scanf("%d", &y);
    printf("x = %d, y = %d\n", x, y);
    wasa(wa, sa, x, y);   // 適切な引数の指定をする
    printf("wa = x+y = %d\nsa = x-y", wa, sa);
    return 0;
}

void wasa(wa, sa, x, y){
    int sum = x + y;
    int def = x - y; 
    char *wa = &sum;
    char *sa = &def;
}