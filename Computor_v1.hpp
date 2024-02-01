#ifndef COMPUTOR_V1_HPP
# define COMPUTOR_V1_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "StringTools.hpp"
# include "MathTools.hpp"
# include <vector>
# include <map>
# include <iomanip>

static const bool ommitFactorZero = false;

class Computor_v1
{
	private:
		std::string output;
		std::string input;
		std::string treating;
		std::vector<std::string> terms;
		std::map<size_t, double> factors;
		bool valid_terms;
		size_t degree;
		std::string reduced_form;
		double discriminant; // delta
		std::map<size_t, complex_t> results;
		std::string message;

	public:
		Computor_v1(const std::string& u_input);
		Computor_v1(Computor_v1 const&);
		Computor_v1& operator= (Computor_v1 const&);
		~Computor_v1();

	private:
		Computor_v1();

	public:
		const std::string& getOutput() const;
		const std::string& getInput() const;
		const std::string& getTreating() const;
		const std::vector<std::string>& getTerms() const;
		const std::map<size_t, double>& getFactors() const;
		const bool& getValidTerms() const;
		const size_t& getDegree() const;
		const std::string& getReducedForm() const;
		const double& getDiscriminant() const;
		const std::map<size_t, complex_t>& getResults() const;
		const std::string& getMessage() const;

	private:
		void run();
		void treat_spaces();
		void treat_implicits();
		void mount_terms();
		void validate_terms();
		void set_equal_to_zero();
		void discriminate_factors();
		void gen_reduced_form();
		void gen_discriminant();
		void gen_results();
		void gen_output();
};

std::ostream& operator<< (std::ostream&, Computor_v1 const&);

#endif
