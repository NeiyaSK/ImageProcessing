// 課題No.03-C

#define PI 3.141592653589793

#include <stdio.h>
#include <math.h>
typedef double t_id;

double deg2rad(t_id deg);
double deg_sin(t_id deg);
double deg_cos(t_id deg);

int main(void)
{
    double deg[] = {0, 45, 90, 120, 180, -90, -120};
    int n = sizeof(deg)/sizeof(deg[0]);

    for (int i=0; i < n; i++)
    {
        printf("%.1f [deg] = %f [rad] \n", deg[i], deg2rad(deg[i]));
        printf("sin(%.1f[deg]) = %f, cos(%.1f[deg]) = %f\n\n", deg[i], deg_sin(deg[i]), deg[i], deg_cos(deg[i]));
    }
    return 0;
}

double deg2rad(t_id deg)
{
    double rad = deg * PI/180;

    return rad;
}

double deg_sin(t_id deg)
{
    double rad = deg2rad(deg);
    double sum = rad;
    double t = rad;
    int i;
    for(i = 1; i < 10; i++)
    {
        t *= -(rad*rad)/((i*2)*(i*2+1));
        sum += t;
    }
    return sum;
}

double deg_cos(t_id deg)
{
    double sin = deg_sin(deg);
    double cos = sqrt(1 - sin*sin);
    return cos;
}

