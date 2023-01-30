#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>
double Exp(double x) {

    double termSum = 1.0;
    double seriesSum = termSum;

    //Computing e^x
    double k = 1.0; //what is k how does it become a factorial
    while (termSum > EPSILON) {
        termSum *= Abs(x) / k;
        seriesSum += termSum;
        k += 1;
    }
    if (x > 0) {
        return seriesSum;
    } else {
        return (1 / seriesSum);
    }
}

double Sin(double x) {
    double seriesValue = x;
    double currentSeriesValue = 1.0;
    double termValue = x;
    double k = 3.0;

    while (Abs(termValue) > EPSILON) {
        termValue = termValue * (x * x) / ((k - 1) * k);
        currentSeriesValue = -currentSeriesValue;
        seriesValue += currentSeriesValue * termValue;
        k += 2;
    }
    return seriesValue;
}

double Cos(double x) {
    double seriesValue = 1;
    double currentSeriesValue = 1.0;
    double termValue = x;
    double k = 2.0;

    while (Abs(termValue) > EPSILON) {
        termValue = termValue * (x * x) / ((k - 1) * k);
        currentSeriesValue = -currentSeriesValue;
        seriesValue += currentSeriesValue * termValue;
        k += 2;
    }
    return seriesValue;
}
double Sqrt(double x) {
    double currentTerm = 0.0;
    double nextTerm = 1.0;
    double offSet = 1.0;

    //Scaling
    while (x > 1) {
        x /= 4.0;
        offSet *= 2.0; //2^(k+1)
    }
    while (Abs(nextTerm - currentTerm) > EPSILON) {
        currentTerm = nextTerm;
        nextTerm = .5 * (currentTerm + (x / nextTerm));
    }
    return nextTerm * offSet;
}

double Log(double x) {
    double seriesSum = 1.0;
    double power = Exp(seriesSum);
    double offSet = 0.0;
    //Scaling
    while (x > Exp(1)) {
        x /= Exp(1);
        offSet += 1.0;
    }
    while (Abs(power - x) > EPSILON) {
        seriesSum = seriesSum + x / power - 1;
        power = Exp(seriesSum);
    }
    return seriesSum + offSet;
}
double integrate(double (*f)(double x), double a, double b, uint32_t n) {
    double upperBound = b;
    double lowerBound = a;
    uint32_t amountOfPartitions = n;
    double h = (upperBound - lowerBound) / amountOfPartitions;
    double seriesSum = (*f)(a) + (*f)(b);

    for (uint32_t i = 2; i < amountOfPartitions; i += 2) {
        seriesSum += 2 * ((*f)(lowerBound + i * h));
    }
    for (uint32_t i = 1; i < amountOfPartitions; i += 2) {
        seriesSum += 4 * ((*f)(lowerBound + i * h));
    }
    seriesSum *= h / 3.0;
    return seriesSum;
}
