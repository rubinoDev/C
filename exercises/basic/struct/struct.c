#include <stdio.h>

struct Car
{
    char brand[10];
    int year;
};

int main()
{
    struct Car c1 = {"Toyota", 2020};
    struct Car c2;
    c2 = c1;
    c2.year = 2021;
    printf("%s %d", c1.brand, c1.year);
    printf("%s %d", c2.brand, c2.year);
}