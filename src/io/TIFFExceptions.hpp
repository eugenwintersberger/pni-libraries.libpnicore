/*
 * TIFFExceptions.hpp
 *
 *  Created on: Sep 26, 2011
 *      Author: eugen
 */

#include "../Exceptions.hpp"

#ifndef TIFFEXCEPTIONS_HPP_
#define TIFFEXCEPTIONS_HPP_

namespace pni{
namespace utils{

class TIFFReadError:public Exception{
public:
	TIFFReadError():Exception("TIFFReadError"){}
	TIFFReadError(const String &i,const String &d):Exception("TIFFReadError",i,d){}
	virtual ~TIFFReadError(){}

	friend std::ostream &operator<<(std::ostream &o,const TIFFReadError &e);
};

//end of namespace
}
}



#endif /* TIFFEXCEPTIONS_HPP_ */
