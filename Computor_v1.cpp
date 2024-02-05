/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor_v1.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:23:27 by fde-capu          #+#    #+#             */
/*   Updated: 2024/02/05 11:18:54 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Computor_v1.hpp"

Computor_v1::Computor_v1(const std::string& u_input)
: input(u_input)
{
	int V(2);
	verbose(V) << "Computor_v1 constructed with input:" << std::endl;
	verbose(V) << this->input << std::endl;
	run();
}

Computor_v1::Computor_v1(Computor_v1 const& src)
{ *this = src; }

Computor_v1& Computor_v1::operator= (Computor_v1 const& rhs)
{
	if (this != &rhs)
	{
		this->output = rhs.getOutput();
		this->input = rhs.getInput();
		this->treating = rhs.getTreating();
		this->terms = rhs.getTerms();
		this->factors = rhs.getFactors();
		this->valid_terms = rhs.getValidTerms();
		this->degree = rhs.getDegree();
		this->reduced_form = rhs.getReducedForm();
		this->discriminant = rhs.getDiscriminant();
		this->results = rhs.getResults();
		this->message = rhs.getMessage();
	}
	return *this;
}

std::ostream& operator<< (std::ostream& o, Computor_v1 const& self)
{
	o << self.getOutput();
	return o;
}

Computor_v1::~Computor_v1(){}

const std::string& Computor_v1::getTreating() const
{ return this->treating; }

const std::string& Computor_v1::getOutput() const
{ return this->output; }

const std::string& Computor_v1::getInput() const
{ return this->input; }

const std::vector<std::string>& Computor_v1::getTerms() const
{ return this->terms; }

const std::map<size_t, double>& Computor_v1::getFactors() const
{ return this->factors; }

const bool& Computor_v1::getValidTerms() const
{ return this->valid_terms; }

const size_t& Computor_v1::getDegree() const
{ return this->degree; }

const std::string& Computor_v1::getReducedForm() const
{ return this->reduced_form; }

const double& Computor_v1::getDiscriminant() const
{ return this->discriminant; }

const std::map<size_t, complex_t>& Computor_v1::getResults() const
{ return this->results; }

const std::string& Computor_v1::getMessage() const
{ return this->message; }
