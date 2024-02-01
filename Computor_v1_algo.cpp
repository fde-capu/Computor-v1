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

void Computor_v1::gen_reduced_form()
{
	int V(2);
	reduced_form = "";
	size_t i = this->degree + 1;
	while (--i <= this->degree)
	{
		if (factors[i] != 0 or !ommitFactorZero)
		{
			reduced_form += factors[i] >= 0.0 ? "+" : "";
			reduced_form += dtoa_clean(factors[i]) + "*x^" + std::to_string(i) + " ";
		}
	}
	if (!reduced_form.length())
		reduced_form = "0 ";
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
			b	(factors[1]),
			c	(factors[0]);

	if (this->degree == 0)
	{
		message = c == 0.0 ? MSG_TAUTOLOGY : MSG_NO_SOLUTION;
	}
	else if (this->degree == 1)
	{
		if (b != 0.0)
		{
			results[0].real = -c / b;
			message = MSG_FIRST_DEGREE;
		}
		else
			message = c == 0.0 ? MSG_TAUTOLOGY : MSG_NO_SOLUTION;
	}
	else // 2nd degree
	{
		if (a != 0.0)
		{
			if (discriminant > 0.0)
			{
				results[0].real = ( -b - sqrt(discriminant) ) / ( 2 * a );
				results[0].imag = 0;
				results[1].real = ( -b + sqrt(discriminant) ) / ( 2 * a );
				results[1].imag = 0;
				message = MSG_DISC_POSITIVE;
			}
			else if (discriminant == 0.0)
			{
				if (2 * a)
					results[0].real = -b / ( 2 * a );
				else
					results[0].real = 0.0;
				results[0].imag = 0;
				message = MSG_DISC_ZERO;
			}
			else if (discriminant < 0.0) // else
			{
				results[0].real = -b / ( 2 * a );
				results[0].imag = sqrt( -discriminant ) / ( 2 * a );
				results[1].real = results[0].real;
				results[1].imag = -results[0].imag;
				message = MSG_DISC_NEG;
			}
		}
		else
			message = MSG_TAUTOLOGY;
	}
	if (!results[0].real)
		noMinusZero(results[0].real);
	if (discriminant && !results[1].real)
		noMinusZero(results[1].real);
}

void Computor_v1::gen_output()
{
	std::stringstream ss;

	if (!valid_terms) return;
	ss << "Reduced form: " << reduced_form << std::endl;
	ss << "Polynomial degree: " << degree << std::endl;
	if (this->degree > 2) message = MSG_OVER_DEGREE;
	if (this->degree == 2)
		ss << "Discriminant (delta): " << discriminant << std::endl;
	ss << message;
	if (message == MSG_NO_SOLUTION)
	{
		output = ss.str();
		return ;
	}
	if (message == MSG_DISC_POSITIVE || message == MSG_DISC_ZERO || message == MSG_DISC_NEG
	|| message == MSG_FIRST_DEGREE)
	{
		ss << std::endl;
		for (auto& r : results)
		{
			ss << std::fixed << std::setprecision(PRECISION);
			ss << r.second.real;
			if (r.second.imag != 0.0)
			{
				ss << std::fixed << std::setprecision(PRECISION - 1);
				ss << (r.second.imag > 0.0 ? "+" : "") << r.second.imag << "i";
			}
			if (message != MSG_FIRST_DEGREE)
				ss << std::endl;
			else
				break;
		}
	}
	output = ss.str();
}
