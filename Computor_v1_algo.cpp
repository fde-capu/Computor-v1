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
			b	(factors[1]),
			c	(factors[0]);

	if (a == 0.0) // 1st degree
	{
		if (b != 0.0)
			results[0].real = -c / b;
		else
		{
			if (c == 0.0)
				message = MSG_TAUTOLOGY;
			else
				message = MSG_NO_SOLUTION;
		}
	}
	else // 2nd degree
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
			results[0].imag = sqrt(-discriminant) / ( 2 * a );
			results[1].real = results[0].real;
			results[1].imag = -results[0].imag;
			message = MSG_DISC_NEG;
		}
	}
	if (!results[0].real)
		noMinusZero(results[0].real);
	if (discriminant && !results[1].real)
		noMinusZero(results[1].real);
}

void Computor_v1::gen_output()
{
	std::stringstream ss;
	ss << "Reduced form: " << reduced_form << std::endl;
	ss << "Polynomial degree: " << degree << std::endl;
	if (this->degree > 2) message = MSG_OVER_DEGREE;
	if (this->degree == 2)
		ss << "Discriminant (delta): " << discriminant << std::endl;
	ss << message;
	ss << std::endl;
	if (message == MSG_DISC_POSITIVE || message == MSG_DISC_ZERO || message == MSG_DISC_NEG)
	{
		for (auto& r : results)
		{
			ss << r.second.real;
			if (r.second.imag != 0.0)
				ss << (r.second.imag > 0.0 ? "+" : "") << r.second.imag << "i";
			ss << std::endl;
		}
	}
	ss << std::endl;
	output = ss.str();
}
