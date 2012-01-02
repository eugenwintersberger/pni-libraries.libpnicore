/*
 * BufferObject.cpp
 *
 *  Created on: Jan 02, 2012
 *      Author: Eugen Wintersberger
 */




#include <boost/python.hpp>


#include "../src/Types.hpp"
#include "../src/BufferObject.hpp"


using namespace pni::utils;
using namespace boost::python;

void wrap_bufferobject(){
    class_<BufferObject,boost::noncopyable>("BufferObject",no_init)
        ;
}

