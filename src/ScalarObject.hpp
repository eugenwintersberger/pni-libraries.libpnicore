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
	ScalarObject();
	ScalarObject(const ScalarObject &o):NumericObject(o){}
	ScalarObject(const String &n,const String &u):NumericObject(n,u){}
	ScalarObject(const char *n,const char *u):NumericObject(n,u){}
	ScalarObject(const String &n,const String &u,const String &d):NumericObject(n,u,d){}
	ScalarObject(const char *n,const char *u,const char *d):NumericObject(n,u,d){}
	virtual ~ScalarObject();

	ScalarObject &operator=(const ScalarObject &o);
};


//end of namespace
}
}


#endif /* SCALAROBJECT_HPP_ */
