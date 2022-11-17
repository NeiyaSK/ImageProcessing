// Example 05-03
#include <stdio.h>
#define N 5
struct Person2 {
    char name[20];
    char age;
};
void func2(struct Person2 *x);

int main(void){
    struct Person2 arr[N];    // 配列で宣言

    for (int i=0; i<N; i++) {
        scanf("%s", arr[i].name);    // 06-01と同様
        scanf("%d", &arr[i].age);    // 06-01と同様
    }
    for (int i=0; i<N; i++)
        func2(&arr[i]);        // アドレスを渡している

    return 0;
}

void func2(struct Person2 *x) {
    printf("Name=%s, ", x->name);
    printf("Age=%d\n", x->age);

    return;
}