#include "Computor_v1.hpp"

void Computor_v1::run()
{
	int V(1);
	treating = input;
	valid_terms = false;

	treat_spaces();
	verbose(V) << "RUNNING" << std::endl;
	mount_terms();
	treat_implicits();
	validate_terms();
	if (!valid_terms) return ;
	set_equal_to_zero();
	discriminate_factors();
	output = "-> TODO, process output";
}

void Computor_v1::treat_spaces()
{
	int V(1);
	verbose(V) << "treat_spaces:" << std::endl;
	substitute_unloop(treating, "X", "x");
	substitute_unloop(treating, "\\t", " ");
	substitute_unloop(treating, "*", " * ");
	substitute_unloop(treating, "+", " + ");
	substitute_unloop(treating, "-", " - ");
	substitute_unloop(treating, "=", " = ");
	substitute_super(treating, " ^", "^");
	substitute_super(treating, "^ ", "^");
	substitute_super(treating, "* ", "*");
	substitute_super(treating, " *", "*");
	substitute_super(treating, "- ", "-");
	substitute_super(treating, "+ ", "+");
	hard_trim(treating);
	verbose(V) << treating << std::endl;
}

void Computor_v1::mount_terms()
{
	int V(1);
	verbose(V) << "mount_terms:" << std::endl;
	substitute_super(treating, "x*x", "xx");
	substitute_super(treating, "x x", "xx");
	substitute_super(treating, " x", "x");
	substitute_super(treating, ".x", "x");
	verbose(V) << treating << std::endl;

	std::pair<size_t, size_t> x_count = find_repeated_char_first_occurance(treating, 'x');
	while (x_count.first != std::string::npos)
	{
		std::string asterisk = 
			x_count.first == 0 ? "" :
			treating.at(x_count.first - 1) == '*' ? "" : 
			isDigit(treating.at(x_count.first - 1)) ? "*" : "";
		treating.replace(x_count.first, x_count.second, asterisk + "x^" + std::to_string(x_count.second));
		substitute_super(treating, "* ", "*");
		substitute_super(treating, " *", "*");
		x_count = find_repeated_char_first_occurance(treating, 'x');
	}

	verbose(V) << "treating: " << treating << std::endl;
	terms = split(treating);
	verbose(V) << "terms (" << terms.size() << "): " << terms << std::endl;
	std::cout << "---" << terms << "---" << std::endl;
	for (auto& t : terms)
		verbose(V) << "-->" << t << std::endl;
}

void Computor_v1::treat_implicits()
{
	int V(1);
	for (auto& c : terms)
	{
		if (c != "=")
			c = "+" + c;
		if (c.find('x') == c.size() - 1)
			c += "^0";
		substitute_unloop(c, "+x", "+1*x");
		substitute_unloop(c, "-x", "-1*x");
		substitute_unloop(c, "+.", "+0.");
		substitute_unloop(c, "-.", "-0.");
		substitute_unloop(c, "+-", "-");
		substitute_unloop(c, "-+", "-");
		substitute_unloop(c, "--", "+");
		substitute_unloop(c, "++", "+");
		substitute_unloop(c, "+-", "-");
		substitute_unloop(c, "-+", "-");
		if (isNumber(c)) c += "*x^0";
		substitute_unloop(c, "--", "+"); // Again.
		substitute_unloop(c, "++", "+"); // Again.
	}
	verbose(V) << "treat_implicits:" << std::endl;
	verbose(V) << terms << std::endl;
}

void Computor_v1::validate_terms()
{
	valid_terms = true;
	std::string point_to_error = "";
	size_t point_position = 0;
	std::string error_reason = "";

	for (auto& t : terms)
	{
		char step = 0;
		bool got_factor = false;
		for (size_t i = 0; i < t.size(); i++)
		{
			if ((step == 0) \
			&& ((t.at(i) == '-' || t.at(i) == '+')
				|| (t.at(i) == '=' && t.size() == 1)))
			{
				step++;
				continue ;
			}
			if (step == 1)
			{
				if (isNumberChar(t.at(i)))
				{
					got_factor = true;
					continue ;
				}
				else
				{
					if (got_factor)
						step++;
				}
			}
			if ((step == 2) \
			&& (t.at(i) == '*'))
			{
				step++;
				continue ;
			}
			if ((step == 3) \
			&& (t.at(i) == 'x'))
			{
				step++;
				continue ;
			}
			if ((step == 4) \
			&& (t.at(i) == '^'))
			{
				step++;
				continue ;
			}
			if (step == 5 && isDigit(t.at(i)))
			{
				continue ;
			}
			valid_terms = false;
			point_to_error = t;
			point_position = i;
			error_reason =
				step == 0 ? "Expected one and only one '+' or '-' mark." :
				step == 1 ? "Expected factor." :
				step == 2 ? "Expected '*x^n'." :
				step == 3 ? "Expected 'x^n'." :
				step == 4 ? "Expected '^n'." :
				step == 5 ? "Expected term power." :
					"~~~ (8> Cosmic ray detected! <8) ~~~";
			if (!valid_terms) break ;
		}
		if (!valid_terms) break ;
	}
	if (valid_terms)
		return ;
	std::cerr << "Detected invalid terms. " << point_to_error << std::endl;
	std::cerr << (std::string(point_position, ' ') + "^ " + error_reason) << std::endl;
}

void Computor_v1::set_equal_to_zero()
{
	int V(1);
	bool before_equal_sign = true;
	std::vector<std::string> zero_equal_equation = {};

	for (auto& t : terms)
	{
		if (t == "=")
		{
			before_equal_sign = false;
			continue ;
		}
		if (!before_equal_sign)
		{
			if (t.at(0) == '+')
				t = "-" + t.substr(1);
			else if (t.at(0) == '-')
				t = "+" + t.substr(1);
		}
		zero_equal_equation.push_back(t);
	}
	terms = zero_equal_equation;
	verbose(V) << "set_equal_to_zero" << std::endl;
	verbose(V) << terms << std::endl;
}

void Computor_v1::discriminate_factors()
{
	int V(0);
	double fact;
	size_t deg;
	this->degree = 0;

	factors = {};
	for (auto& term : terms)
	{
		fact = std::stod(term.c_str());
		deg = std::atoi(get_after_first(term, "^").c_str());
		verbose(V) << "(" << term << ") factor " << fact << " degree " << deg << std::endl;
		factors[degree] += fact;
		degree = deg > degree && factors[degree] != 0.0 ? deg : degree;
		verbose(V) << (std::to_string(degree) + "> " + std::to_string(factors[degree])) << std::endl;
	}
	
	verbose(V) << "discriminate_factors Equation degree: " << this->degree << std::endl;
	size_t i = -1;
	while (++i < 10)
	{
		verbose(V) << (std::to_string(i) + ") " + std::to_string(factors[i])) << std::endl;
	}
}
