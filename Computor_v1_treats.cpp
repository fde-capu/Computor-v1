#include "Computor_v1.hpp"

void Computor_v1::treat_spaces()
{
	int V(2);

	verbose(V) << "treat_spaces input: " << this->treating << std::endl;
	substitute_unloop(this->treating, "X", "x");
	substitute_unloop(this->treating, "\\s", " ");
	substitute_unloop(this->treating, "*", " * ");
	substitute_unloop(this->treating, "/", " / ");
	substitute_unloop(this->treating, "+", " + ");
	substitute_unloop(this->treating, "-", " - ");
	substitute_unloop(this->treating, "=", " = ");
	substitute_super(this->treating, " ^", "^");
	substitute_super(this->treating, "^ ", "^");
	substitute_super(this->treating, "* ", "*");
	substitute_super(this->treating, " *", "*");
	substitute_super(this->treating, "/ ", "/");
	substitute_super(this->treating, " /", "/");
	substitute_super(this->treating, "- ", "-");
	substitute_super(this->treating, "+ ", "+");
	substitute_super(this->treating, "  ", " ");
	hard_trim(this->treating);
	verbose(V) << "treat_spaces result: " << this->treating << std::endl;
}

void Computor_v1::mount_terms()
{
	int V(2);

	verbose(V) << "mount_terms:" << std::endl;
	substitute_super(this->treating, "x*x", "xx");
	substitute_super(this->treating, "x x", "xx");
	substitute_super(this->treating, " x", "x");
	substitute_super(this->treating, ".x", "x");
	for (size_t i = 0; i < 10; i++)
		substitute_super(this->treating, "x " + itoa(i), "x*" + itoa(i));
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
			substitute_super(this->treating, itoa(i) + " " + itoa(j), itoa(i) + "*" + itoa(j));
	}
	verbose(V) << this->treating << std::endl;
	std::pair<size_t, size_t> x_count = find_char_sequence(this->treating, 'x');
	while (x_count.first != std::string::npos)
	{
		verbose(V+1) << "(mount_terms) x_count " << x_count.first << ", " << x_count.second << std::endl;
		std::string asterisk = 
			x_count.first == 0 ? "" :
			this->treating.at(x_count.first - 1) == '*' ? "" : 
			isDigit(this->treating.at(x_count.first - 1)) ? "*" : "";
		std::string power = std::to_string(x_count.second);
		if (x_count.first + x_count.second >= this->treating.size()
			|| (
					this->treating.at(x_count.first + x_count.second) == ' ' 
				)
			)
			this->treating.replace(x_count.first, x_count.second, asterisk + "x^" + power);
		substitute_super(this->treating, "* ", "*");
		substitute_super(this->treating, " *", "*");
		x_count = find_char_sequence(this->treating, 'x', x_count.first + 3 + power.length());
	}
	verbose(V+1) << "(mount_terms) this->treating: " << this->treating << std::endl;
	this->terms = split(this->treating);
	verbose(V) << "(mount_terms) this->terms (" << this->terms.size() << "): " << this->terms << std::endl;
}

void Computor_v1::treat_implicits()
{
	int V(2);

	verbose(V) << "(treat_implicits) input: " << this->terms << std::endl;
	for (auto& c : this->terms)
	{
		substitute_unloop(c, "0x", "0*x");
		substitute_unloop(c, "1x", "1*x");
		substitute_unloop(c, "2x", "2*x");
		substitute_unloop(c, "3x", "3*x");
		substitute_unloop(c, "4x", "4*x");
		substitute_unloop(c, "5x", "5*x");
		substitute_unloop(c, "6x", "6*x");
		substitute_unloop(c, "7x", "7*x");
		substitute_unloop(c, "8x", "8*x");
		substitute_unloop(c, "9x", "9*x");
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
		if (isAllInSet(c, "-+.^0123456789")) c += "*x^0";
		substitute_unloop(c, "x*", "x^1*");
	}
	verbose(V) << "(treat_implicits) result: " << this->terms << std::endl;
}

void Computor_v1::validate_terms()
{
	int V(2);
	this->valid_terms = true;
	std::string point_to_error = "";
	size_t point_position = 0;
	std::string error_reason = "";

	for (auto& t : this->terms)
	{
		verbose(V) << "(validate_terms): " << t << std::endl;
		char step = 0;
		bool got_factor = false;
		bool x_found = false;
		bool getting_degree = false;
		bool got_op = false;
		for (size_t i = 0; i < t.size(); i++)
		{
			if ((step == 0) \
			&& ((t.at(i) == '-' || t.at(i) == '+')
				|| (t.at(i) == '=' && t.size() == 1)))
			{
				verbose(V) << "step 0: " << t.at(i) << std::endl;
				step++; continue ;
			}
			if (step == 1)
			{
				verbose(V) << "step 1: " << t.at(i) << std::endl;
				if (t.at(i) == '.' && getting_degree)
					step = 5;
				else if (isNumberChar(t.at(i)))
					{ got_factor = true; continue ; }
				else if (got_factor)
					step++;
			}
			if (step == 2 && isInSet(t.at(i), "*/^x"))
			{
				verbose(V) << "step 2: " << t.at(i) << std::endl;
				getting_degree = false;
				got_op = false;
				if (isInSet(t.at(i), "*/"))
					{ step++; got_op = true; continue ; }
				else if (t.at(i) == '^')
				{
					getting_degree = true;
					if (!x_found)
						{ step = 5; continue ; }
					else
						{ step = 6 ; }
				}
				else if (t.at(i) == 'x')
					step++;
			}
			if (step == 3)
			{
				verbose(V) << "step 3: " << t.at(i) << std::endl;
				if (t.at(i) == 'x')
					{ x_found = true; step++; continue ; }
				if (isInSet(t.at(i), "+-/*^") && got_op)
					step = 7;
				else if (isInSet(t.at(i), "+-/*^") || isDigit(t.at(i)))
					{ step = 1; continue ; }
			}
			if (step == 4)
			{
				verbose(V) << "step 4: " << t.at(i) << std::endl;
				if (t.at(i) == '^')
					{ getting_degree = true; step++; continue ; }
				if (isInSet(t.at(i), "+-/*") || isDigit(t.at(i)))
					{ step = 1; continue ; }
			}
			if (step == 5)
			{
				verbose(V) << "step 5: " << t.at(i) << std::endl;
				if (t.at(i) == '+')
					continue ;
				if (isDigit(t.at(i)))
					{ step = 1; continue ; }
			}
			this->valid_terms = false;
			point_to_error = t;
			point_position = i;
			error_reason =
				step == 0 ? "Expected one and only one '+' or '-' mark." :
				step == 1 ? "Expected factor." :
				step == 2 ? "Expected '*x^n'." :
				step == 3 ? "Expected 'x^n'." :
				step == 4 ? "Expected '^n'." :
				step == 5 ? "Unexpected character. Power must be positive integer. Negative power not implemented." :
				step == 6 ? "Expected end of term or */ operators." :
				step == 7 ? "Syntax error." :
					"~~~ (8> Cosmic ray detected! <8) ~~~";
			if (!this->valid_terms) break ;
		}
		if (!this->valid_terms) break ;
	}
	if (this->valid_terms)
		return ;
	std::cerr << "Detected invalid terms:" << std::endl << point_to_error << std::endl;
	std::cerr << (std::string(point_position, ' ') + "^ " + error_reason) << std::endl;
}

void Computor_v1::set_equal_to_zero()
{
	int V(2);
	bool before_equal_sign = true;
	std::vector<std::string> zero_equal_equation = {};
	this->inputElements = 0;

	for (auto& t : this->terms)
		this->inputElements += t != "=" && stod(t) != 0.0;

	for (auto& t : this->terms)
	{
		if (t == "=")
		{
			before_equal_sign = false;
			continue ;
		}
		if (!before_equal_sign)
		{
			if (t.at(0) == '+')
				t = this->inputElements > 1 ? "-" + t.substr(1) : t;
			else if (t.at(0) == '-')
				t = this->inputElements > 1 ? "+" + t.substr(1) : t;
		}
		zero_equal_equation.push_back(t);
	}
	this->terms = zero_equal_equation;
	verbose(V) << "(set_equal_to_zero) " << this->terms << std::endl;
}

void Computor_v1::discriminate_factors()
{
	int V(2);
	double fact;
	size_t deg;
	this->degree = 0;
	this->factors = {};

	for (auto& term : this->terms)
	{
		std::string fact_equation = remove_x_ponential(term);
		verbose(V) << "(discriminate_factors) factor equation: " << fact_equation << std::endl;
		fact = solveEquation(fact_equation);
		verbose(V) << "(discriminate_factors) solved: " << fact << std::endl;
		deg = std::atoi(get_after_first(term, "x^").c_str());
		verbose(V) << "(discriminate_factors) (" << term << ") factor "
			<< fact << " degree " << deg << std::endl;
		this->factors[deg] += fact;
		int highestDegree = -1;
		for (auto it = this->factors.rbegin(); it != this->factors.rend(); ++it)
		{
			if (it->second != 0)
			{
				highestDegree = it->first;
				break;
			}
		}
		this->degree = highestDegree <= 0 ? 0 : highestDegree;
		verbose(V+1) << "(discriminate_factors) deg is "
			<< (std::to_string(this->degree) + " after seeing "
			+ std::to_string(this->factors[deg])) << std::endl;
	}
	verbose(V) << "(discriminate_factors) Polynomial degree: " << this->degree \
		<< std::endl;
	size_t i = -1;
	while (++i <= this->degree)
		verbose(V) << "(discriminate_factors) degree " << std::to_string(i) + \
			" value = " + std::to_string(this->factors[i]) << std::endl;
}
