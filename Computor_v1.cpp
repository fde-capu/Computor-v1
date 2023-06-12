/* ******************************************* */
/*                                             */
/*                     ::::::|::::||:::|:|:::| */
/* Computor_v1.cpp     ||::|::|:||::||:|::|||| */
/*                     :|:|:|||:||:||||||::::: */
/*                                             */
/*                                             */
/* C20230612141443                             */
/* U20230612141444 |||:::                      */
/*                                             */
/* ******************************************* */

#include "Computor_v1.hpp"

Computor_v1::Computor_v1()
{
	Debug("Computor_v1 constructed.");	
}

Computor_v1::Computor_v1(Computor_v1 const& src)
{
	*this = src;
}

Computor_v1& Computor_v1::operator= (Computor_v1 const& rhs)
{
	if (this != &rhs)
	{
//		this->member = rhs.getMember();
	}
	return *this;
}

std::ostream& operator<< (std::ostream& o, Computor_v1 const& self)
{
	o << "::Computor_v1::" << std::endl;
	static_cast<void>(self);
	return o;
}

Computor_v1::~Computor_v1()
{
	Debug("Computor_v1 destructed.");	
}
