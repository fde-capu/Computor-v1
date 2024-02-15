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
			verbose(V) << "(gen_reduced_form a) " << this->reduced_form << std::endl;
			this->reduced_form += dtoa(this->factors[i]) + "*x^" + \
				std::to_string(i) + " ";
			verbose(V) << "(gen_reduced_form b) " << this->reduced_form << std::endl;
		}
	}
	if (!this->reduced_form.length())
	{
		this->reduced_form = "0 ";
		verbose(V) << "(gen_reduced_form c) " << this->reduced_form << std::endl;
	}
	this->reduced_form += "= 0";
	verbose(V) << "(gen_reduced_form) " << this->reduced_form << std::endl;
}

void Computor_v1::gen_discriminant()
{
	int V(1);
	double	a	(this->factors[2]),
			b	(this->factors[1]),
			c	(this->factors[0]);

	this->discriminant = ( b * b ) - ( 4 * a * c );
	verbose(V) << "(gen_discriminant) ( b * b ) - ( 4 * a * c ): " << \
		"( " << dtoa(b * b) << " ) - " << dtoa(4 * a * c) << " = " << \
		dtoa(this->discriminant) << std::endl;
}

void Computor_v1::gen_results()
{
	int V(1);
	double	a	(this->factors[2]),
			b	(this->factors[1]),
			c	(this->factors[0]);

	verbose(V) << "(gen_results) a " << dtoa(a) << " b " << dtoa(b) << " c " << \
		dtoa(c) << std::endl;
	if (this->degree == 0)
	{
		verbose(V) << "(gen_results) degree == 0: " << dtoa(this->degree) << std::endl;
		if (c == 0.0)
		{
			verbose(V) << "(gen_results) c == 0.0: " << dtoa(c) << std::endl;
			this->message = MSG_TAUTOLOGY;
		}
		else
		{
			verbose(V) << "(gen_results) c != 0.0: " << dtoa(c) << std::endl;
			this->message = MSG_NO_SOLUTION;
		}
	}
	else if (this->degree == 1)
	{
		verbose(V) << "(gen_results) degree == 1: " << dtoa(this->degree) << std::endl;
		if (b != 0.0)
		{
			verbose(V) << "(gen_results) b != 0.0: " << dtoa(b) << std::endl;
			this->results[0].real = -c / b;
			verbose(V) << "(gen_results) results[0].real (-c/b) " << \
				dtoa(-c) << "/" << dtoa(b) << " = " << \
				dtoa(this->results[0].real) << std::endl;
			this->message = MSG_FIRST_DEGREE;
		}
		else
		{
			verbose(V) << "(gen_results) b == 0.0: " << dtoa(b) << std::endl;
			if (c == 0.0)
			{
				verbose(V) << "(gen_results) c == 0.0: " << dtoa(c) << std::endl;
				this->message = MSG_TAUTOLOGY;
			}
			else
			{
				verbose(V) << "(gen_results) c != 0.0: " << dtoa(c) << std::endl;
				this->message = MSG_NO_SOLUTION;
			}
		}
	}
	else // 2nd degree
	{
		verbose(V) << "(gen_results) degree == 2: " << dtoa(this->degree) << std::endl;
		if (a != 0.0)
		{
			verbose(V) << "(gen_results) a != 0.0: " << dtoa(a) << std::endl;
			if (this->discriminant > 0.0)
			{
				verbose(V) << "(gen_results) discriminant > 0.0: " << \
					dtoa(this->discriminant) << std::endl;
				this->results[0].real = ( -b - sqrt(this->discriminant) ) \
										/ ( 2 * a );
				verbose(V) << "(gen_results) [0].real (-b-sqr(delta))/2a " << \
					"( " << dtoa(-b) << " - " << \
					dtoa(sqrt(this->discriminant)) << \
					" ) / " << dtoa(2 * a) << " = " << \
					dtoa(this->results[0].real) << std::endl;
				this->results[0].imag = 0;
				verbose(V) << "(gen_results) [0].imag is 0: " << \
					dtoa(this->results[0].imag) << std::endl;
				this->results[1].real = ( -b + sqrt(this->discriminant) ) \
										/ ( 2 * a );
				verbose(V) << "(gen_results) [0].real (-b+sqr(delta))/2a " << \
					"( " << dtoa(-b) << " + " << \
					dtoa(sqrt(this->discriminant)) << \
					" ) / " << dtoa(2 * a) << " = " << \
					dtoa(this->results[1].real) << std::endl;
				this->results[1].imag = 0;
				verbose(V) << "(gen_results) [1].imag is 0: " << \
					dtoa(this->results[1].imag) << std::endl;
				this->message = MSG_DISC_POSITIVE;
			}
			else if (this->discriminant == 0.0)
			{
				verbose(V) << "(gen_results) discriminant == 0.0: " << \
					dtoa(this->discriminant) << std::endl;
				if (2 * a)
				{
					verbose(V) << "(gen_results) 2 * a != 0.0: " << \
						dtoa(2 * a) << std::endl;
					this->results[0].real = -b / ( 2 * a );
					verbose(V) << "(gen_results) [0].real (-b/2a) " << \
						dtoa(-b) << "/" << dtoa(2 * a) << " = " << \
						dtoa(this->results[0].real) << std::endl;
				}
				else
				{
					verbose(V) << "(gen_results) 2 * a == 0.0: " << \
						dtoa(2 * a) << std::endl;
					this->results[0].real = 0.0;
					verbose(V) << "(gen_results) [0].real can only be 0: " << \
						dtoa(this->results[0].real) << std::endl;
				}
				this->results[0].imag = 0;
				verbose(V) << "(gen_results) [0].imag can only be 0: " << \
					dtoa(this->results[0].imag) << std::endl;
				this->message = MSG_DISC_ZERO;
			}
			else if (this->discriminant < 0.0) // else
			{
				verbose(V) << "(gen_results) discriminant < 0.0: " << \
					dtoa(this->discriminant) << std::endl;
				this->results[0].real = -b / ( 2 * a );
				verbose(V) << "(gen_results) [0].real (-b/2a) " << \
					dtoa(-b) << "/" << dtoa(2 * a) << " = " << \
					dtoa(this->results[0].real) << std::endl;
				this->results[0].imag = sqrt( -this->discriminant ) / ( 2 * a );
				verbose(V) << "(gen_results) [0].imag: " << \
					"sqrt(-discriminant)/2a: " << "sqrt(-" << \
					dtoa(-discriminant) << ") / ( 2 * " << dtoa(a) << " )" << \
					"-> " << dtoa(sqrt(-this->discriminant)) << \
					" / " << dtoa(2 * a) << " = " << \
					dtoa(this->results[0].imag) << "i" << std::endl;
				this->results[1].real = this->results[0].real;
				verbose(V) << "(gen_results) [1].real (-b/2a) " << \
					dtoa(-b) << "/" << dtoa(2 * a) << " = " << \
					dtoa(this->results[1].real) << std::endl;
				this->results[1].imag = -this->results[0].imag;
				verbose(V) << "(gen_results) [1].imag = -[0].imag" << 
					" = " << dtoa(this->results[1].imag) << "i" << std::endl;
				this->message = MSG_DISC_NEG;
			}
		}
		else
		{
			verbose(V) << "(gen_results) a == 0.0: " << dtoa(a) << std::endl;
			this->message = MSG_TAUTOLOGY;
		}
	}
	if (!this->results[0].real)
	{
		verbose(V) << "(gen_results) [0].real == 0.0: " << \
			dtoa(this->results[0].real) << std::endl;
		noMinusZero(this->results[0].real);
		verbose(V) << "(gen_results) [0].real corrected -0: " << \
			dtoa(this->results[0].real) << std::endl;
	}
	if (this->discriminant && !this->results[1].real)
	{
		verbose(V) << "(gen_results) discriminant != 0.0 && [1].real == 0.0: discriminant: " \
			<< dtoa(this->discriminant) << ", [1].real: " << \
			dtoa(this->results[1].real) << std::endl;
		noMinusZero(this->results[1].real);
		verbose(V) << "(gen_results) [0].real corrected -0: " << \
			dtoa(this->results[0].real) << std::endl;
	}
	verbose(V) << "(gen_results) message " << this->message << std::endl;
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

	if (!this->valid_terms) return ;
	ss << "Reduced form: " << this->reduced_form << std::endl;
	ss << "Polynomial degree: " << this->degree << std::endl;
	if (this->degree > 2) this->message = MSG_OVER_DEGREE;
	if (this->degree == 2)
		ss << "Discriminant (delta): " << fixInt(this->discriminant) << \
			std::endl;
	ss << this->message;
	if (this->message == MSG_NO_SOLUTION)
	{
		this->output = ss.str();
		return ;
	}
	if (this->message == MSG_DISC_POSITIVE || this->message == MSG_DISC_ZERO \
		|| this->message == MSG_DISC_NEG || this->message == MSG_FIRST_DEGREE)
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
