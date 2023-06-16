#ifndef DEBUG_HPP
# define DEBUG_HPP

# include <iostream>
# include <vector>
# include "defines.hpp"
# include "StringTools.hpp"

class Debug
{
	public:
		static bool power;
		static void on();
		static void off();
		static void onoff();
		static std::string charTable;
		std::string label;
		std::string debug_string;
		bool delimiter;
		Debug();
		Debug(std::string u_string);
		Debug(const std::vector<std::string>& u_vector);
		Debug(std::string label, std::string u_string, bool delimiter = false);
		Debug(std::string label, size_t number);
		~Debug();
};

std::ostream& operator<< (std::ostream&, Debug const&);

#endif
