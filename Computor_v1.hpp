/* ******************************************* */
/*                                             */
/*                     ::::::|::::||:::|:|:::| */
/* Computor_v1.hpp     ||::|::|:||::||:|::|||| */
/*                     :|:|:|||:||:||||||::::: */
/*                                             */
/*                                             */
/* C20230612141439 |:||||                      */
/* U20230612141440 :|::|:                      */
/*                                             */
/* ******************************************* */

#ifndef COMPUTOR_V1_HPP
# define COMPUTOR_V1_HPP

# include <iostream>
# include <string>
# include "Debug.hpp"

class Computor_v1
{
	public:
		Computor_v1();
		Computor_v1(Computor_v1 const&);
		Computor_v1& operator= (Computor_v1 const&);
		~Computor_v1();
};

std::ostream& operator<< (std::ostream&, Computor_v1 const&);

#endif
