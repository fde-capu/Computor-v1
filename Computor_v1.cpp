#include "Computor_v1.hpp"

Computor_v1::Computor_v1(const std::string& u_input)
: input(u_input)
{
	int V(1);
	verbose(V) << "Computor_v1 constructed with input:" << std::endl;
	verbose(V) << input << std::endl;
	run();
}

Computor_v1::Computor_v1(Computor_v1 const& src)
{ *this = src; }

Computor_v1& Computor_v1::operator= (Computor_v1 const& rhs)
{
	if (this != &rhs)
	{
		output = rhs.getOutput();
		input = rhs.getInput();
		treating = rhs.getTreating();
		terms = rhs.getTerms();
		factors = rhs.getFactors();
		valid_terms = rhs.getValidTerms();
		degree = rhs.getDegree();
		reduced_form = rhs.getReducedForm();
		message = rhs.getMessage();
	}
	return *this;
}

std::ostream& operator<< (std::ostream& o, Computor_v1 const& self)
{
	o << self.getOutput();
	return o;
}

Computor_v1::~Computor_v1()
{ Debug("Computor_v1 destructed."); }

const std::string& Computor_v1::getTreating() const
{ return treating; }

const std::string& Computor_v1::getOutput() const
{ return output; }

const std::string& Computor_v1::getInput() const
{ return input; }

const std::vector<std::string>& Computor_v1::getTerms() const
{ return terms; }

const std::map<size_t, double>& Computor_v1::getFactors() const
{ return factors; }

const bool& Computor_v1::getValidTerms() const
{ return valid_terms; }

const size_t& Computor_v1::getDegree() const
{ return degree; }

const std::string& Computor_v1::getReducedForm() const
{ return reduced_form; }

const std::string& Computor_v1::getMessage() const
{ return message; }
