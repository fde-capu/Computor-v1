/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor_v1_treats.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:26:06 by fde-capu          #+#    #+#             */
/*   Updated: 2024/02/05 13:43:25 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Computor_v1.hpp"

void Computor_v1::treat_spaces()
{
	int V(2);

	verbose(V) << "treat_spaces:" << std::endl;
	substitute_unloop(this->treating, "X", "x");
	substitute_unloop(this->treating, "\\t", " ");
	substitute_unloop(this->treating, "*", " * ");
	substitute_unloop(this->treating, "+", " + ");
	substitute_unloop(this->treating, "-", " - ");
	substitute_unloop(this->treating, "=", " = ");
	substitute_super(this->treating, " ^", "^");
	substitute_super(this->treating, "^ ", "^");
	substitute_super(this->treating, "* ", "*");
	substitute_super(this->treating, " *", "*");
	substitute_super(this->treating, "- ", "-");
	substitute_super(this->treating, "+ ", "+");
	hard_trim(this->treating);
	verbose(V) << this->treating << std::endl;
}

void Computor_v1::mount_terms()
{
	int V(2);

	verbose(V) << "mount_terms:" << std::endl;
	substitute_super(this->treating, "x*x", "xx");
	substitute_super(this->treating, "x x", "xx");
	substitute_super(this->treating, " x", "x");
	substitute_super(this->treating, ".x", "x");
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
	}
	verbose(V) << "(treat_implicits): " << this->terms << std::endl;
}

void Computor_v1::validate_terms()
{
	this->valid_terms = true;
	std::string point_to_error = "";
	size_t point_position = 0;
	std::string error_reason = "";

	for (auto& t : this->terms)
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
			this->valid_terms = false;
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
			if (!this->valid_terms) break ;
		}
		if (!this->valid_terms) break ;
	}
	if (this->valid_terms)
		return ;
	std::cerr << "Detected invalid this->terms:" << std::endl << point_to_error << std::endl;
	std::cerr << (std::string(point_position, ' ') + "^ " + error_reason) << std::endl;
}

void Computor_v1::set_equal_to_zero()
{
	int V(2);
	bool before_equal_sign = true;
	std::vector<std::string> zero_equal_equation = {};

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
				t = "-" + t.substr(1);
			else if (t.at(0) == '-')
				t = "+" + t.substr(1);
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
		fact = std::stod(term.c_str());
		deg = std::atoi(get_after_first(term, "^").c_str());
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
		verbose(V+1) << "(discriminate_factors) "
			<< (std::to_string(this->degree) + "> "
			+ std::to_string(this->factors[deg])) << std::endl;
	}
	verbose(V) << "(discriminate_factors) Polynomial degree: " << this->degree << std::endl;
	size_t i = -1;
	while (++i <= this->degree)
		verbose(V) << "(discriminate_factors) " << (std::to_string(i) + ") " \
			+ std::to_string(this->factors[i]) + " " \
			+ std::to_string(this->degree)) << std::endl;
}
