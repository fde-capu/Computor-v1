#include "Computor_v1.hpp"

void Computor_v1::run()
{
	treating = input;
	treat_spaces();
	mount_terms();
	treat_implicits();
	validate_terms();
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
	bool valid = true;
	for (auto& t : terms)
	{
		if (isNumber(t)) continue;
		valid = false;
	}
	if (valid)
		return ;
	Debug("Detected invalid terms.");
}
