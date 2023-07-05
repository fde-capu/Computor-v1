#include "MathTools.hpp"

double sqrt(double number)
{
    double error = 0.000001;
    double guess = number;

    while (guess - (number / guess) > error)
        guess = (guess + (number / guess)) / 2;
    return guess;
}

void noMinusZero(double& d)
{
	std::string noMinus = dtoa_clean(d);
	if (noMinus.at(0) == '-')
		noMinus = noMinus.substr(1);
	d = std::stod(noMinus.c_str());
}
