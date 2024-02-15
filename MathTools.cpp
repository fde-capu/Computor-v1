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
	double out_p;
	double pp;
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
	std::vector<std::string> pow = split(e, "^");
	out_p = out_m * out_d;
	pp = out_p;
	for (size_t i = 1; i < pow.size(); i++)
	{
		verbose(V) << "(solveEquation) " << dtoa(out_p) << " ^ " << pow[i] << std::endl;
		for (size_t p = 1; p < std::stod(pow[i].c_str()); p++)
		{
			verbose(V) << "(solveEquation) partial power: " << dtoa(out_p) << " * " << dtoa(pp) << std::endl;
			out_p *= pp;
			verbose(V) << "(solveEquation) power = " << dtoa(out_p) << std::endl;
		}
		verbose(V) << "(solveEquation) = " << dtoa(out_p) << std::endl;
	}
	out = out_p;
	verbose(V) << "(solveEquation) Result: " << dtoa(out) << std::endl;
	return out;
}
