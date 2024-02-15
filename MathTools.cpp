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

double solveEquation(const std::string& e)
{
	int V(2);
	double out_m;
	double out_d;
	double out;

	verbose(V) << "(solveEquation) Solving: " << e << std::endl;
	std::vector<std::string> mult = split(e, "*");
	out_m = 1;
	for (size_t i = 0; i < mult.size(); i++)
	{
		if (!mult[i].length())
			continue ;
		verbose(V) << "(solveEquation) " << dtoa(out_m) << " * " << mult[i] << std::endl;
		double m = std::stod(mult[i].c_str());
		verbose(V) << "(solveEquation) m: " << dtoa(m) << std::endl;
		out_m *= m;
		verbose(V) << "(solveEquation) = " << dtoa(out_m) << std::endl;
	}
	std::vector<std::string> div = split(e, "/");
	out_d = 1;
	for (size_t i = 1; i < div.size(); i++)
	{
		verbose(V) << "(solveEquation) " << dtoa(out_d) << " / " << div[i] << std::endl;
		out_d /= std::stod(div[i].c_str());
		verbose(V) << "(solveEquation) = " << dtoa(out_d) << std::endl;
	}
	out = out_m * out_d;
	verbose(V) << "(solveEquation) Result: " << dtoa(out) << std::endl;
	return out;
}
