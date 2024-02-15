#include "header.hpp"

void help()
{
	std::cout << "Computor v1 @42 by fde-capu" << std::endl;
	std::cout << "Usage: ./computor args" << std::endl;
	std::cout << std::endl;
	std::cout << "args examples:" << std::endl << std::endl;
	std::cout << "  " << "\"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"" << std::endl;
	std::cout << "  " << "Result:" << std::endl;
	std::cout << "  " << "Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0" << std::endl;
	std::cout << "  " << "Polynomial degree: 2" << std::endl;
	std::cout << "  " << "Discriminant is strictly positive, the two solutions are:" << std::endl;
	std::cout << "  " << "0.905239" << std::endl;
	std::cout << "  " << "-0.475131" << std::endl;
	std::cout << std::endl;
	std::cout << "  " << "5 * X^0 + 4 * X^1 = 4 * X^0\"" << std::endl;
	std::cout << "  " << "Result:" << std::endl;
	std::cout << "  " << "Reduced form: 1 * X^0 + 4 * X^1 = 0" << std::endl;
	std::cout << "  " << "Polynomial degree: 1" << std::endl;
	std::cout << "  " << "The solution is:" << std::endl;
	std::cout << "  " << "-0.25" << std::endl;
	std::cout << std::endl;
	std::cout << "  " << "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0\"" << std::endl;
	std::cout << "  " << "Result:" << std::endl;
	std::cout << "  " << "Reduced form: 5 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 0" << std::endl;
	std::cout << "  " << "Polynomial degree: 3" << std::endl;
	std::cout << "  " << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
	std::cout << std::endl;
	std::cout << "Alternative notation:" << std::endl;
	std::cout << "  " << "`./computor a b c` will process as second degree factors." << std::endl;
}

std::string argJoin(int argc, char** argv)
{
	int V(2);
	size_t i = argc;
	std::string out(" ");
	std::vector<std::string> plain;
	bool plain_pass = true;

	while (i-- > 1)
		out = std::string(argv[i]) + " " + out;
	hard_trim(out);
	verbose(V) << "(argJoin) A) " << out << std::endl;
	// alternative notation 'a b c':
	if (isAllInSet(out, "0123456789 +-.") && argc == 4)
	{
		out = std::string(argv[1]) + "*x^2 " \
			+ argv[2] + "*x^1 " \
			+ argv[3] + "*x^0 = 0";
	}
	if (isAllInSet(out, "0123456789 +-.") && argc == 2)
	{
		plain = split(out);
		for (size_t i = 0; i < plain.size(); i++)
		{
			if (isAllInSet(plain[i], "0123456789 +-."))
				continue ;
			else
			{
				plain_pass = false;
				break ;
			}
		}
		if (plain_pass)
		{
			out = std::string(plain[0]) + "*x^2 " \
				+ plain[1] + "*x^1 " \
				+ plain[2] + "*x^0 = 0";
		}
	}
	verbose(V) << "(argJoin) B) " << out << std::endl;
	return out;
}

std::string getEqOriginal(int argc, char** argv)
{
	return argJoin(argc, argv);
}

bool validateArgCount(int argc, char** argv)
{
	if (!argc || argc == 1)
		return false;
	(void)argv;
	return true;
}

int main (int argc, char** argv)
{
	std::cout << std::fixed << std::setprecision(PRECISION);
	std::string equation_raw;

	if (!validateArgCount(argc, argv))
	{ help(); return 1; }

	equation_raw = getEqOriginal(argc, argv);
	if (equation_raw == "--help"
	||	equation_raw == "-h"
	||	equation_raw == "-?")
	{ help(); return 0; }

	Computor_v1 result(equation_raw);
	std::cout << result << std::endl;
	return result.getValidTerms() ? 0 : 1;
}
