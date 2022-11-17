// Example 05-07: 動的配列
#include <stdio.h>
#include <stdlib.h>
int main(void){
    int n;
    scanf("%d", &n);  // 配列の要素数を入力
    
    // intのサイズ×要素数分の領域を確保して、
    // intポインタ型にキャストして返す
    int *arr = (int *)malloc(sizeof(int) * n);
    
    for(int i=0; i < n; i++) 
        arr[i] = i * i; // *(arr+i) = i * i; でも同じこと
    
    for(int i=0; i < n; i++)
        printf("arr[%d] = %d\n", i, arr[i]);
        
    free(arr);
    arr = NULL;
    
    return 0;
}