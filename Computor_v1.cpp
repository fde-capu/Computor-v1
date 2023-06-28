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
		input = rhs.getInput();
		output = rhs.getOutput();
		treating = rhs.getTreating();
		terms = rhs.getTerms();
		// TODO: get other properties.
		valid_terms = rhs.getIsValidTerms();
	}
	return *this;
}

std::ostream& operator<< (std::ostream& o, Computor_v1 const& self)
{
	o << self.getOutput() << std::endl;
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

bool Computor_v1::getIsValidTerms() const
{ return valid_terms; }
