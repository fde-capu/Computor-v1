#include "Debug.hpp"

bool Debug::power(DEBUG);
std::string Debug::charTable("\"\"");

Debug::Debug()
: label(""), debug_string("-BUG-"), delimiter(false)
{ std::cout << *this << std::endl; }

Debug::Debug(std::string u_string)
: label(""), debug_string(u_string), delimiter(false)
{ std::cout << *this << std::endl; }

Debug::Debug(const std::vector<std::string>& u_vector)
: label(""), debug_string("[ "), delimiter(false)
{
	for (auto& v : u_vector)
		debug_string += v + " , ";
	debug_string += " ]";
	substitute_all(debug_string, ",  ]", "]");
	std::cout << *this << std::endl;
}

Debug::Debug(std::string label, std::string u_string, bool delimiter)
: label(label), debug_string(u_string), delimiter(delimiter)
{ std::cout << *this << std::endl; }

std::ostream& operator<< (std::ostream& o, Debug const& self)
{
	if (self.label.length())
		o << self.label << std::endl;
	if (self.delimiter)
		o << Debug::charTable.at(0);
	o << self.debug_string;
	if (self.delimiter)
		o << Debug::charTable.at(1);
	return o;
}

Debug::~Debug() {}

void Debug::on()
{ power = true; }

void Debug::off()
{ power = false; }

void Debug::onoff()
{ power = !power; }
