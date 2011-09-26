/*
 * TIFFExceptions.cpp
 *
 *  Created on: Sep 26, 2011
 *      Author: eugen
 */


#include "TIFFExceptions.hpp"

namespace pni{
namespace utils{

std::ostream &operator<<(std::ostream &o,const TIFFReadError &e){
	return e.print(o);
}

//end of namespace
}
}



