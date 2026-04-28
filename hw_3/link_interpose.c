#include <stdio.h>

void fred(int arg)
{
    printf("interposed fred is called, arg = %d\n", arg);
}

void john(double arg)
{
    printf("interposed john is called, arg = %f\n", arg);
}