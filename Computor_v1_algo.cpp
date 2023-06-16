#include "Computor_v1.hpp"

void Computor_v1::run()
{
	treating = input;
	valid_terms = false;

	treat_spaces();
	mount_terms();
	treat_implicits();
//	validate_terms();
	if (!valid_terms) return ;
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
	Debug("treat_spaces:", treating, true);
}

void Computor_v1::mount_terms()
{
	terms = split(treating);
	Debug("mount_terms:");
	(Debug(terms));
}

void Computor_v1::treat_implicits()
{
	for (auto& c : terms)
	{
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
		if (isDigit(c.at(0))) c = "+" + c;
		if (isNumber(c)) c += "*x^0";
		substitute_unloop(c, "--", "+"); // Again.
		substitute_unloop(c, "++", "+"); // Again.
	}
	Debug("treat_implicits:");
	(Debug(terms));
}

void Computor_v1::validate_terms() const
{
	char step = 0;
	bool valid = true;
	std::string point_to_error = "";
	size_t point_position = 0;
	std::string error_reason = "";

	for (auto& t : terms)
	{
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
					continue ;
				else
					step++;
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
			valid = false;
			point_to_error = t;
			point_position = i;
			error_reason =
				step == 0 ? "Expected one and only one '+' or '-' mark." :
				step == 1 ? "Expected NumberChars followed by '*x^n'." :
				step == 2 ? "Expected '*x^n'." :
				step == 3 ? "Expected 'x^n'." :
				step == 4 ? "Expected '^n'." :
				step == 5 ? "Expected term power." :
					"Cosmic ray hit.";
			Debug("point_position", i);
			if (!valid) break ;
		}
		if (!valid) break ;
	}
	if (valid)
		return ;
	Debug("Detected invalid terms.", point_to_error);
	Debug(std::string(point_position - 1, ' ') + "^ " + error_reason);
}
