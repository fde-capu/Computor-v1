#include "Computor_v1.hpp"

void Computor_v1::run()
{
	treating = input;
	valid_terms = false;

	treat_spaces();
	mount_terms();
	treat_implicits();
	validate_terms();
	if (!valid_terms) return ;
	set_equal_to_zero();
	output = "-> TODO, process output";
}

void Computor_v1::treat_spaces()
{
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
}

void Computor_v1::mount_terms()
{
	substitute_super(treating, "x x", "xx");
	std::pair<size_t, size_t> x_count = find_repeated_char_first_occurance(treating, 'x');
	while (x_count.first != std::string::npos)
	{
		treating.replace(x_count.first, x_count.second, "x^" + std::to_string(x_count.second));
		x_count = find_repeated_char_first_occurance(treating, 'x');
	}

	terms = split(treating);
	Debug("mount_terms:");
	(Debug(terms));
}

void Computor_v1::treat_implicits()
{
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
	Debug("treat_implicits:");
	(Debug(terms));
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
	Debug("Detected invalid terms.", point_to_error);
	Debug(std::string(point_position, ' ') + "^ " + error_reason);
}

void Computor_v1::set_equal_to_zero()
{
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
	Debug("set_equal_to_zero");
	(Debug(terms));
}
