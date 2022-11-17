// Example 05-02
#include <stdio.h>
#include <math.h>

struct Person{
    char name[20];
    char age;
    double weight;  // kg
    double height;  // cm
};

struct Index{
    double bmi;
    double standard;    // BMI=22
    double biyou;       // BMI=20
    double cinderella;  // BMI=18
};

struct Index calc(struct Person x);
void print(struct Person p, struct Index x);

int main(void)
{
    struct Person b = {"Hanako", 18, 55, 160};
    struct Index r = calc(b);
    print(b, r);   
    return 0;
}

struct Index calc(struct Person x)
{
    /* data */
    struct Index ind;
    ind.bmi = x.weight / ((x.height/100) *(x.height/100));
    ind.standard = x.height/100 * x.height/100 * 22;
    ind.biyou = x.height/100 * x.height/100 * 20;
    ind.cinderella = x.height/100 * x.height/100 * 18;

    return ind;
}

void print(struct Person p, struct Index x) {
    printf("[%s]\n", p.name);
    printf("  age: %d\n", p.age);
    printf("  weight: %.1f kg\n", p.weight);
    printf("  height: %.1f cm\n\n", p.height);

    printf("BMI = %.2f\n", x.bmi);
    printf("-----------------------------------\n");
    printf("  standard weight(BMI=22) = %.1f kg\n", x.standard);
    printf("     biyou weight(BMI=20) = %.1f kg\n", x.biyou);
    printf("cinderella weight(BMI=18) = %.1f kg\n", x.cinderella);
    // printf("     model weight(BMI=17) = %.1f kg\n", x.model);
    return;
}