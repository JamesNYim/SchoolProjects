#include "mathlib.h"

#include <math.h>
#include <stdio.h>

int main(void) {
    printf("hello world\n");

    printf("My exp: %.14lf \n", Exp(1));
    printf("Actual exp: %.14lf \n", exp(1));
    printf("\n");

    printf("My sin: %.14lf \n", Sin(1));
    printf("Actual sin: %.14lf \n", sin(1));
    printf("\n");

    printf("My cos: %.14lf \n", Cos(1));
    printf("Actual cos: %.14lf \n", cos(1));
    printf("\n");

    printf("My sqrt: %.14lf \n", Sqrt(1));
    printf("Actual sqrt: %.14lf \n", sqrt(1));
    printf("\n");

    printf("My log: %.14lf \n", Log(29));
    printf("Actual log: %.14lf \n", log(29));
    printf("\n");
}
