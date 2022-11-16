// 課題No.03-A
// 課題No.03-B
#include <stdio.h>

int my_greater(int a, int b); // No.03-A
int my_abs(signed int a); // No.03-B

int main(void)
{
int a,b;
scanf("%d", &a);
scanf("%d", &b);
printf("a = %d, b = %d\n", a, b);
printf("%d is greater.\n", my_greater(a, b));
printf("my_abs(%d) = %d\n", a, my_abs(a));
printf("my_abs(%d) = %d\n", b, my_abs(b));

return 0;
}

int my_greater(int a, int b)
{
int greater;
if(a<b)
greater = b;
else
greater = a;

return greater;
}

int my_abs(signed int a)
{
int local_abs;
if(a<0)
local_abs = -a;
else
local_abs = a;

return local_abs;
}

// 課題No.03-C
// 課題No.03-D