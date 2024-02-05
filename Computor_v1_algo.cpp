/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor_v1_algo.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:23:59 by fde-capu          #+#    #+#             */
/*   Updated: 2024/02/05 11:11:26 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Computor_v1.hpp"

void Computor_v1::run()
{
	int V(2);
	verbose(V) << "Computor_v1::run()" << std::endl;
	this->treating = this->input;
	this->valid_terms = false;
	treat_spaces();
	mount_terms();
	treat_implicits();
	validate_terms();
	if (!this->valid_terms) return ;
	set_equal_to_zero();
	discriminate_factors();
	gen_reduced_form();
	gen_discriminant();
	gen_results();
	gen_output();
}

void Computor_v1::gen_reduced_form()
{
	int V(2);
	this->reduced_form = "";
	size_t i = this->degree + 1;
	while (--i <= this->degree)
	{
		if (!ommitFactorZero)
		{
			this->reduced_form += this->factors[i] >= 0.0 ? "+" : "";
			this->reduced_form += dtoa_clean(this->factors[i]) + "*x^" + std::to_string(i) + " ";
		}
	}
	if (!this->reduced_form.length())
		this->reduced_form = "0 ";
	this->reduced_form += "= 0";
	verbose(V) << "(this->reduced_form) " << this->reduced_form << std::endl;
}

void Computor_v1::gen_discriminant()
{
	double	a	(this->factors[2]),
			b	(this->factors[1]),
			c	(this->factors[0]);

	this->discriminant = ( b * b ) - ( 4 * a * c );
}

void Computor_v1::gen_results()
{
	double	a	(this->factors[2]),
			b	(this->factors[1]),
			c	(this->factors[0]);

	if (this->degree == 0)
	{
		this->message = c == 0.0 ? MSG_TAUTOLOGY : MSG_NO_SOLUTION;
	}
	else if (this->degree == 1)
	{
		if (b != 0.0)
		{
			this->results[0].real = -c / b;
			this->message = MSG_FIRST_DEGREE;
		}
		else
			this->message = c == 0.0 ? MSG_TAUTOLOGY : MSG_NO_SOLUTION;
	}
	else // 2nd degree
	{
		if (a != 0.0)
		{
			if (this->discriminant > 0.0)
			{
				this->results[0].real = ( -b - sqrt(this->discriminant) ) / ( 2 * a );
				this->results[0].imag = 0;
				this->results[1].real = ( -b + sqrt(this->discriminant) ) / ( 2 * a );
				this->results[1].imag = 0;
				this->message = MSG_DISC_POSITIVE;
			}
			else if (this->discriminant == 0.0)
			{
				if (2 * a)
					this->results[0].real = -b / ( 2 * a );
				else
					this->results[0].real = 0.0;
				this->results[0].imag = 0;
				this->message = MSG_DISC_ZERO;
			}
			else if (this->discriminant < 0.0) // else
			{
				this->results[0].real = -b / ( 2 * a );
				this->results[0].imag = sqrt( -this->discriminant ) / ( 2 * a );
				this->results[1].real = this->results[0].real;
				this->results[1].imag = -this->results[0].imag;
				this->message = MSG_DISC_NEG;
			}
		}
		else
			this->message = MSG_TAUTOLOGY;
	}
	if (!this->results[0].real)
		noMinusZero(this->results[0].real);
	if (this->discriminant && !this->results[1].real)
		noMinusZero(this->results[1].real);
}

std::string fixInt(double n)
{
	std::stringstream s;
	std::vector<std::string> intTest;

	s << std::fixed << std::setprecision(PRECISION);
	s << n;
	intTest = split(s.str(), ".");
	if (isAllInSet(intTest[1], "0i"))
		return intTest[0] == "-0" ? "0" : intTest[0];
	s.str("");
	if (n == static_cast<int>(n))
		s << std::fixed << std::setprecision(0);
	else
		s << std::fixed << std::setprecision(PRECISION);
	s << n;
	return s.str();
}

void Computor_v1::gen_output()
{
	std::stringstream ss;

	if (!this->valid_terms) return;
	ss << "Reduced form: " << this->reduced_form << std::endl;
	ss << "Polynomial degree: " << this->degree << std::endl;
	if (this->degree > 2) this->message = MSG_OVER_DEGREE;
	if (this->degree == 2)
		ss << "Discriminant (delta): " << fixInt(this->discriminant) << std::endl;
	ss << this->message;
	if (this->message == MSG_NO_SOLUTION)
	{
		this->output = ss.str();
		return ;
	}
	if (this->message == MSG_DISC_POSITIVE || this->message == MSG_DISC_ZERO || this->message == MSG_DISC_NEG
	|| this->message == MSG_FIRST_DEGREE)
	{
		ss << std::endl;
		for (auto& r : this->results)
		{
			ss << fixInt(r.second.real);
			if (r.second.imag != 0.0)
			{
				ss << (r.second.imag > 0.0 ? "+" : "");
				ss << fixInt(r.second.imag) << "i";
			}
			if (this->message != MSG_FIRST_DEGREE)
				ss << std::endl;
			else
				break;
		}
	}
	this->output = ss.str();
}
