#include <stdio.h>
<<<<<<< HEAD
#define N 1
=======
#define N 3
>>>>>>> a0956db05f0dde679e44f603a50551e84e966964

typedef struct{
    int id; // id
    char name[20];  // 名前
    int kokugo, sansu, rika;    // 国語、算数、理科の点数
} SEISEKI;


int main(void){
    SEISEKI seiseki[N];
    for(int i=0; i < N; i++){
        printf("id : \n");
        scanf("%d", &seiseki[i].id);
        if(seiseki[i].id < 0)
            break;
        printf("name : \n");
        scanf("%s", &seiseki[i].name);
        printf("kokugo : \n");
        scanf("%d", &seiseki[i].kokugo);
        printf("sansu : \n");
        scanf("%d", &seiseki[i].sansu);
        printf("rika : \n");
        scanf("%d", &seiseki[i].rika);
    }

    int n = 0;
    int kokugo = 0;
    int sansu = 0;
    int rika = 0;
<<<<<<< HEAD
    for(int i=0; seiseki[i].id >= 0 && i <= 100; i++){
=======
    for(int i=0; seiseki[i].id >= 0 && i < N; i++)
    {
>>>>>>> a0956db05f0dde679e44f603a50551e84e966964
        printf("%d: %s %d\n", seiseki[i].id, seiseki[i].name, (seiseki[i].kokugo + seiseki[i].sansu + seiseki[i].rika) / 3);
        n++;
        kokugo += seiseki[i].kokugo;
        sansu += seiseki[i].sansu;
        rika += seiseki[i].rika;
    }
    printf("kokugo = %d\n", kokugo / n);
    printf("sansu = %d\n", sansu / n);
    printf("rika = %d\n", rika / n);

    return 0;
}