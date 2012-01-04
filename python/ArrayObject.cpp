/*
 * ArrayObject.cpp
 *
 *  Created on: Jan 02, 2012
 *      Author: Eugen Wintersberger
 */


#include <boost/python.hpp>

#include "../src/Types.hpp"
#include "../src/ArrayObject.hpp"

using namespace pni::utils;
using namespace boost::python;

void wrap_arrayobject(){
    class_<ArrayObject,bases<NumericObject>,boost::noncopyable>("ArrayObject",no_init)
        ;
}
