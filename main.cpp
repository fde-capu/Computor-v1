#include "header.hpp"

void help()
{
		std::cout << "Computor v1 @42 by fde-capu" << std::endl;
		std::cout << "Usage: ./computor args" << std::endl;
		std::cout << "args examples:" << std::endl;
		std::cout << "\t" << "\"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"" << std::endl;
		std::cout << "\t" << "Result:" << std::endl;
		std::cout << "\t\t" << "Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0" << std::endl;
		std::cout << "\t\t" << "Polynomial degree: 2" << std::endl;
		std::cout << "\t\t" << "Discriminant is strictly positive, the two solutions are:" << std::endl;
		std::cout << "\t\t" << "0.905239" << std::endl;
		std::cout << "\t\t" << "-0.475131" << std::endl;
		std::cout << "\t" << "5 * X^0 + 4 * X^1 = 4 * X^0\"" << std::endl;
		std::cout << "\t\t" << "Result:" << std::endl;
		std::cout << "\t\t" << "Reduced form: 1 * X^0 + 4 * X^1 = 0" << std::endl;
		std::cout << "\t\t" << "Polynomial degree: 1" << std::endl;
		std::cout << "\t\t" << "The solution is:" << std::endl;
		std::cout << "\t\t" << "-0.25" << std::endl;
		std::cout << "\t" << "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0\"" << std::endl;
		std::cout << "\t\t" << "Result:" << std::endl;
		std::cout << "\t\t" << "Reduced form: 5 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 0" << std::endl;
		std::cout << "\t\t" << "Polynomial degree: 3" << std::endl;
		std::cout << "\t\t" << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
}

std::string argJoin(int argc, char** argv)
{
	std::string out("");

	while (argc-- > 1)
		out = std::string(argv[argc]) \
			+ (out.length() ? " " : "") \
			+ out;
	return out;
}

std::string getEqOriginal(int argc, char** argv)
{
	if (argc > 2)
		return argJoin(argc, argv);
	else
		return std::string(argv[1]);
}

bool validateArgCount(int argc, char** argv)
{
	if (!argc || argc == 1)
	{
		return false;
	}
	(void)argv;
	return true;
}

std::string treat(const std::string& eqo)
{
	std::string out(eqo);
	substitute_unloop(out, "X", "x");
	substitute_unloop(out, "*", " * ");
	substitute_unloop(out, "+", " + ");
	substitute_unloop(out, "-", " - ");
	substitute_unloop(out, "=", " = ");
	substitute_unloop(out, " ^", "^");
	substitute_unloop(out, "^ ", "^");
	hard_trim(out);
	substitute_unloop(out, "- ", "-");
	substitute_unloop(out, "+ ", "+");
	substitute_unloop(out, "* ", "*");
	substitute_unloop(out, " *", "*");
	substitute_unloop(out, "+x", "+1*x");
	substitute_unloop(out, "-x", "-1*x");
	substitute_unloop(out, "+.", "+0.");
	substitute_unloop(out, "-.", "-0.");
	substitute_super(out, "+-", "-");
	substitute_super(out, "-+", "-");
	substitute_super(out, "--", "+");
	substitute_super(out, "++", "+");
	substitute_super(out, "+-", "-");
	substitute_super(out, "-+", "-");
	return out;
}

std::vector<float> parse(const std::string& eqo)
{
	std::vector<float> out;
	size_t i = -1;
	while (++i < eqo.length())
	{
	}
	return out;
}

bool validateTerms(const std::vector<std::string>& u_terms)
{
	for (auto& t : u_terms)
	{
		if (isNumber(t)) continue;
	}
	return false;
}

void fullSyntax(std::vector<std::string>& u_)
{
	for (auto& t : u_)
	{
		if (isDigit(t.at(0))) t = "+" + t;
		if (isNumber(t)) t += "*x^0";
	}
}

int main (int argc, char** argv)
{
	std::string eq_original;
	std::string eq_treated;
	std::vector<std::string> terms;

	if (!validateArgCount(argc, argv))
	{ help(); return 1; }

	eq_original = getEqOriginal(argc, argv);
	eq_treated = treat(eq_original);
	Debug("eq_treated", eq_treated, true);

	terms = split(eq_treated);
	(Debug(terms));

	fullSyntax(terms);
	(Debug(terms));

	if (!validateTerms(terms))
	{ std::cout << "Invalid terms." << std::endl; return 1; }

//	eq = parse(eq_original);
	return 0;
}
