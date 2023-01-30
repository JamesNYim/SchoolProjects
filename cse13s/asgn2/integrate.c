#include "functions.h"
#include "mathlib.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Prints an integral based off of a set of functions.\n"
        "\n"
        "USAGE\n"
        "   %s [-abcdefghin:p:q:H] [-abcdefghi functions] [-n amount of partitions] [-p lower "
        "bounds of the integral] [-q upper bounds of the integral] [ -H displays the help page]\n"
        "\n"
        "OPTIONS\n"
        "   -a         sqrt(1 - x^4)\n"
        "   -b         1 / log(x)\n"
        "   -c         e^(-x^2)\n"
        "   -d         sin(x^2)\n"
        "   -e         cos(x^2)\n"
        "   -f         log(log(x))\n"
        "   -g         sin(x) / x\n"
        "   -h         (e^-x) / (x)\n"
        "   -i         e^(e^x)\n"
        "   -j         sqrt(sin^2(x) + cos^2(x))\n"
        "   -n         Sets the amount of partitions to use in the integral. Has a default value "
        "of 100.\n"
        "   -p         Sets the lower bounds of the integral. It does not have a default value.\n"
        "   -q         Sets the upper bounds of the integral. It does not have a default value.\n"
        "   -H         Shows the help page\n",
        exec);
}

int main(int argc, char **argv) {
    int opt = 0;
    int amountOfPartitions = 100;
    double lowerBound;
    double upperBound;
    bool aCase = false;
    bool bCase = false;
    bool cCase = false;
    bool dCase = false;
    bool eCase = false;
    bool fCase = false;
    bool gCase = false;
    bool hCase = false;
    bool iCase = false;
    bool jCase = false;
    //Choosing which function to integrate
    while ((opt = getopt(argc, argv, "abcdefghijn:p:q:H")) != -1) {
        switch (opt) {
        case 'a': aCase = true; break;
        case 'b': bCase = true; break;
        case 'c': cCase = true; break;
        case 'd': dCase = true; break;
        case 'e': eCase = true; break;
        case 'f': fCase = true; break;
        case 'g': gCase = true; break;
        case 'h': hCase = true; break;
        case 'i': iCase = true; break;
        case 'j': jCase = true; break;
        case 'n': amountOfPartitions = strtod(optarg, NULL); break;
        case 'p': lowerBound = strtod(optarg, NULL); break;
        case 'q': upperBound = strtod(optarg, NULL); break;
        case 'H': usage(argv[0]); return EXIT_FAILURE;

        default:
            fprintf(stderr, "No options were given or certain options were not properly inputted. "
                            "Please try again (see ./integrate -H) \n");
            return 1;
        }
    }

    //calling the functions to integrate a certain amount of times
    if (aCase) {
        printf("sqrt(1 - x^4), %0.6f, %0.6f, %d\n", lowerBound, upperBound, amountOfPartitions);
        for (int i = 2; i <= amountOfPartitions; i += 2) {
            printf("%d,%0.15f\n", i, integrate(a, lowerBound, upperBound, i));
        }
    }
    if (bCase) {

        printf("1/log(x), %0.6f, %0.6f, %d\n", lowerBound, upperBound, amountOfPartitions);
        for (int i = 2; i <= amountOfPartitions; i += 2) {
            printf("%d,%0.15f\n", i, integrate(b, lowerBound, upperBound, i));
        }
    }
    if (cCase) {

        printf("e^(-x^2), %0.6f, %0.6f, %d\n", lowerBound, upperBound, amountOfPartitions);
        for (int i = 2; i <= amountOfPartitions; i += 2) {
            printf("%d,%0.15f\n", i, integrate(c, lowerBound, upperBound, i));
        }
    }
    if (dCase) {

        printf("sin(x^2), %0.6f, %0.6f, %d\n", lowerBound, upperBound, amountOfPartitions);
        for (int i = 2; i <= amountOfPartitions; i += 2) {
            printf("%d,%0.15f\n", i, integrate(d, lowerBound, upperBound, i));
        }
    }
    if (eCase) {

        printf("cos(x^2), %0.6f, %0.6f, %d\n", lowerBound, upperBound, amountOfPartitions);
        for (int i = 2; i <= amountOfPartitions; i += 2) {
            printf("%d,%0.15f\n", i, integrate(e, lowerBound, upperBound, i));
        }
    }
    if (fCase) {

        printf("log(log(x)), %0.6f, %0.6f, %d\n", lowerBound, upperBound, amountOfPartitions);
        for (int i = 2; i <= amountOfPartitions; i += 2) {
            printf("%d,%0.15f\n", i, integrate(f, lowerBound, upperBound, i));
        }
    }
    if (gCase) {

        printf("sin(x)/x, %0.6f, %0.6f, %d\n", lowerBound, upperBound, amountOfPartitions);
        for (int i = 2; i <= amountOfPartitions; i += 2) {
            printf("%d,%0.15f\n", i, integrate(g, lowerBound, upperBound, i));
        }
    }
    if (hCase) {

        printf("e^(-x)/x), %0.6f, %0.6f, %d\n", lowerBound, upperBound, amountOfPartitions);
        for (int i = 2; i <= amountOfPartitions; i += 2) {
            printf("%d,%0.15f\n", i, integrate(h, lowerBound, upperBound, i));
        }
    }
    if (iCase) {

        printf("e^(e^x), %0.6f, %0.6f, %d\n", lowerBound, upperBound, amountOfPartitions);
        for (int j = 2; j <= amountOfPartitions; j += 2) {
            printf("%d,%0.15f\n", j, integrate(i, lowerBound, upperBound, j));
        }
    }
    if (jCase) {

        printf("sqrt(sin^2(x) + cos^2(x)), %0.6f, %0.6f, %d\n", lowerBound, upperBound,
            amountOfPartitions);
        for (int i = 2; i <= amountOfPartitions; i += 2) {
            printf("%d,%0.15f\n", i, integrate(j, lowerBound, upperBound, i));
        }
    }
    return 0;
}
