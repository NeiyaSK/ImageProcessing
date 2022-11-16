// 課題No.03-C

#define PI 3.141592653589793

#include <stdio.h>

double deg2rad(double deg);
double deg_sin(double deg);
double deg_cos(double deg);

int main(void)
{
    double deg[] = {0, 45, 90, 120, 180, -90, -120};
    int n = sizeof(deg)/sizeof(deg[0]);

    for (int i=0; i < n; i++)
    {
        printf("%.1f [deg] = %f [rad] \n", deg[i], deg2rad(deg[i]));
        printf("sin($.1f[deg]) = %f, cos(%.1f[deg]) = %f\n\n", deg[i], deg_sin(deg[i]), deg[i], deg_cos(deg[i]));
    }
    return 0;
}

double deg2rad(deg)
{
    double rad = deg * (PI/180);

    return rad;
}

int deg_sin(deg)
{
    double rad = deg * (PI/180);
    int rem = 0;
    double t=rad;
    int i;
    for(i = 0; t >0 ; i++)
    {
        t -= rad / (2 * PI);

    }

}

