#include "MathTools.hpp"

double sqrt(double number)
{
    double error = 0.000001;
    double guess = number;

    while (guess - (number / guess) > error)
        guess = (guess + (number / guess)) / 2;
    return guess;
}
