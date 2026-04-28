#include <stdio.h>
#include "lib.h"

static void my_bill(char *arg)
{
    printf("interposed bill is called, arg = %s\n", arg);
}

static void my_sam(double arg)
{
    printf("interposed sam is called, arg = %f\n", arg);
}

struct interpose_entry {
    const void *replacement;
    const void *original;
};

__attribute__((used))
static const struct interpose_entry interposers[]
__attribute__((section("__DATA,__interpose"))) = {
    { (const void *)my_bill, (const void *)bill },
    { (const void *)my_sam,  (const void *)sam  }
};