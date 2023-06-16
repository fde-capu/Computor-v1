#ifndef COMPUTOR_V1_HPP
# define COMPUTOR_V1_HPP

# include <iostream>
# include <string>
# include "Debug.hpp"
# include "StringTools.hpp"
# include <vector>

class Computor_v1
{
	private:
		std::string output;
		std::string input;
		std::string treating;
		std::vector<std::string> terms;
		bool valid_terms;

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
		bool getIsValidTerms() const;

	private:
		void run();
		void treat_spaces();
		void treat_implicits();
		void mount_terms();
		void validate_terms() const;
};

std::ostream& operator<< (std::ostream&, Computor_v1 const&);

#endif
