#include "MathTools.hpp"

double sqrt(double number)
{
    double error = 0.000001;
    double guess = 1.0;

	if (number == 0 || number == 1)
		return number;
    while (std::abs((guess * guess) - number) > error)
        guess = (guess + (number / guess)) / 2;
    return guess;
}

void noMinusZero(double& d)
{
	std::string noMinus = dtoa(d);

	if (noMinus.at(0) == '-')
		noMinus = noMinus.substr(1);
	d = std::stod(noMinus.c_str());
}

double pow(const double& base, const size_t& exponent)
{
	int e = exponent;
	double b = base;
	double o = 1;
	while (e--)
		o *= b;
	return o;
}

double solveEquation(const std::string& e)
{
	int V(2);
	double out;
	char op = 0;
	bool negate = false;
	std::vector<std::string> t; // tokens

	verbose(V) << "(solveEquation) Solving: " << e << std::endl;
	t = splitNumbers(e);
	out = std::stod(t[0]);
	negate = out < 0;
	out = std::abs(out);
	for (size_t i = 0; i < t.size(); i++)
	{
		verbose(V) << "(solveEquation) token " << itoa(i) << ": " << t[i] << std::endl;
		if (isInSet(t[i][0], "/*^")) op = t[i][0];
		if (isNumber(t[i]))
		{
			if (op == '/') out /= std::stod(t[i]);
			else if (op == '*') out *= std::stod(t[i]);
			else if (op == '^')
				out = pow(out, std::stod(t[i]));
		}
	}
	if (negate)
		out *= -1;
	verbose(V) << "(solveEquation) Result: " << dtoa(out) << std::endl;
	return out;
}
