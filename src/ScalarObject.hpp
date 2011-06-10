/*
 * ScalarObject.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: eugen
 */

#ifndef SCALAROBJECT_HPP_
#define SCALAROBJECT_HPP_

#include "PNITypes.hpp"
#include "NumericObject.hpp"

namespace pni{
namespace utils{


class ScalarObject:public NumericObject {
public:
	ScalarObject():NumericObject(){}
	ScalarObject(const ScalarObject &o):NumericObject(o){}
	ScalarObject(const String &n,const String &u):NumericObject(n,u){}
	ScalarObject(const char *n,const char *u):NumericObject(n,u){}
	ScalarObject(const String &n,const String &d,const String &u):NumericObject(n,d,u){}
	ScalarObject(const char *n,const char *d,const char *u):NumericObject(n,d,u){}
	virtual ~ScalarObject();
};


//end of namespace
}
}


#endif /* SCALAROBJECT_HPP_ */
