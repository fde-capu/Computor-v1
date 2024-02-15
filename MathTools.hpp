#ifndef MATHTOOLS_HPP
# define MATHTOOLS_HPP

# include "StringTools.hpp"
# include <iostream>

typedef struct Complex {
    double real;
    double imag;
} complex_t;

double sqrt(double);
double pow(const double&, const size_t&);
void noMinusZero(double&);
double solveEquation(const std::string&);

#endif
