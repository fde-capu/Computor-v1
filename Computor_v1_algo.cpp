#include "Computor_v1.hpp"

void Computor_v1::run()
{
	int V(2);
	verbose(V) << "Computor_v1::run()" << std::endl;
	treating = input;
	valid_terms = false;
	treat_spaces();
	mount_terms();
	treat_implicits();
	validate_terms();
	if (!valid_terms) return ;
	set_equal_to_zero();
	discriminate_factors();
	gen_reduced_form();
	gen_discriminant();
	gen_results();
	gen_output();
}

void Computor_v1::treat_spaces()
{
	int V(2);
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
	int V(2);
	verbose(V) << "mount_terms:" << std::endl;
	substitute_super(treating, "x*x", "xx");
	substitute_super(treating, "x x", "xx");
	substitute_super(treating, " x", "x");
	substitute_super(treating, ".x", "x");
	verbose(V) << treating << std::endl;

	std::pair<size_t, size_t> x_count = find_char_sequence(treating, 'x');
	while (x_count.first != std::string::npos)
	{
		verbose(V+1) << "(mount_terms) x_count " << x_count.first << ", " << x_count.second << std::endl;
		std::string asterisk = 
			x_count.first == 0 ? "" :
			treating.at(x_count.first - 1) == '*' ? "" : 
			isDigit(treating.at(x_count.first - 1)) ? "*" : "";
		std::string power = std::to_string(x_count.second);
		if (x_count.first + x_count.second >= treating.size() || treating.at(x_count.first + x_count.second) != '^') 
			treating.replace(x_count.first, x_count.second, asterisk + "x^" + power);
		substitute_super(treating, "* ", "*");
		substitute_super(treating, " *", "*");
		x_count = find_char_sequence(treating, 'x', x_count.first + 3 + power.length());
	}
	verbose(V+1) << "(mount_terms) treating: " << treating << std::endl;
	terms = split(treating);
	verbose(V) << "(mount_terms) terms (" << terms.size() << "): " << terms << std::endl;
}

void Computor_v1::treat_implicits()
{
	int V(2);
	for (auto& c : terms)
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
	}
	verbose(V) << "(treat_implicits): " << terms << std::endl;
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
			if (step == 5 && (isDigit(t.at(i)) || t.at(i) == '+'))
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
				step == 5 ? "Unexpected character. Term power must be positive integer." :
					"~~~ (8> Cosmic ray detected! <8) ~~~";
			if (!valid_terms) break ;
		}
		if (!valid_terms) break ;
	}
	if (valid_terms)
		return ;
	std::cerr << "Detected invalid terms:" << std::endl << point_to_error << std::endl;
	std::cerr << (std::string(point_position, ' ') + "^ " + error_reason) << std::endl;
}

void Computor_v1::set_equal_to_zero()
{
	int V(2);
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
	verbose(V) << "(set_equal_to_zero) " << terms << std::endl;
}

void Computor_v1::discriminate_factors()
{
	int V(2);
	double fact;
	size_t deg;
	this->degree = 0;

	factors = {};
	for (auto& term : terms)
	{
		fact = std::stod(term.c_str());
		deg = std::atoi(get_after_first(term, "^").c_str());
		verbose(V) << "(discriminate_factors) (" << term << ") factor "
			<< fact << " degree " << deg << std::endl;
		factors[deg] += fact;
		this->degree = factors.rbegin()->first;
		verbose(V+1) << "(discriminate_factors) "
			<< (std::to_string(this->degree) + "> "
			+ std::to_string(factors[deg])) << std::endl;
	}
	verbose(V) << "(discriminate_factors) Equation this->degree: " << this->degree << std::endl;
	size_t i = -1;
	while (++i <= this->degree)
		verbose(V) << "(discriminate_factors) " << (std::to_string(i) + ") " + std::to_string(factors[i])) << std::endl;
}

void Computor_v1::gen_reduced_form()
{
	int V(2);
	reduced_form = "";
	size_t i = this->degree + 1;
	while (--i <= this->degree)
	{
		reduced_form += factors[i] >= 0.0 ? "+" : "";
		reduced_form += dtoa_clean(factors[i]) + "*x^" + std::to_string(i) + " ";
	}
	reduced_form += "= 0";
	verbose(V) << "(reduced_form) " << reduced_form << std::endl;
}

void Computor_v1::gen_discriminant()
{
	double	a	(factors[2]),
			b	(factors[1]),
			c	(factors[0]);

	discriminant = ( b * b ) - ( 4 * a * c );
}

void Computor_v1::gen_results()
{
	double	a	(factors[2]),
			b	(factors[1]);

	if (discriminant > 0.0)
	{
		results[0].real = ( -b - sqrt(discriminant) ) / ( 2 * a );
		results[0].imag = 0;
		results[1].real = ( -b + sqrt(discriminant) ) / ( 2 * a );
		results[1].imag = 0;
	}
	else if (discriminant == 0.0)
	{
		if (2 * a)
			results[0].real = -b / ( 2 * a );
		else
			results[0].real = 0.0;
		results[0].imag = 0;
	}
	else if (discriminant < 0.0) // else
	{
		results[0].real = -b / ( 2 * a );
        results[0].imag = sqrt(-discriminant) / ( 2 * a );
		results[1].real = results[0].real;
		results[1].imag = -results[0].imag;
	}
	if (!results[0].real)
		noMinusZero(results[0].real);
	if (discriminant && !results[1].real)
		noMinusZero(results[1].real);
}

void Computor_v1::gen_output()
{
	int V(1);
	std::stringstream ss;
	ss << "Reduced form: " << reduced_form << std::endl;
	ss << "Polynomial degree: " << degree << std::endl;
	if (this->degree > 2)
	{
		ss << "The polynomial degree is strictly greater than 2, I can't solve.";
	}
	else
	{
		if (V > 0)
			ss << "Discriminant (delta): " << discriminant << std::endl;
		ss << (discriminant > 0.0 ? "Discriminant is strictly positive, the two solutions are:"
		: discriminant == 0.0 ? "Discriminant is zero, the polynomial has exactly one real root:"
		: "Discriminant is negative, the polinomial has two distinct complex roots.");
		ss << std::endl;
		for (auto& r : results)
		{
			ss << r.second.real;
			if (r.second.imag != 0.0)
				ss << (r.second.imag > 0.0 ? "+" : "") << r.second.imag << "i";
			ss << std::endl;
		}
	}

	ss << std::endl;
	ss << message << std::endl;
	output = ss.str();
}
