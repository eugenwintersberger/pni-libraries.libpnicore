/*
 * Shape.cpp
 *
 *  Created on: Dec 22, 2011
 *      Author: Eugen Wintersberger
 */




#include <boost/python.hpp>


#include "../src/Types.hpp"
#include "../src/Shape.hpp"


using namespace pni::utils;
using namespace boost::python;

void wrap_shape(){
	//====================Wrapping ArrayShape===================================
	size_t (Shape::*shape_get_rank)() const = &Shape::rank;
	void   (Shape::*shape_set_rank)(const size_t &) = &Shape::rank;
	size_t (Shape::*shape_get_dimension)(const size_t &) const = &Shape::dim;
	void   (Shape::*shape_set_dimension)(const size_t &,const size_t &) = &Shape::dim;
	class_<Shape>("Shape")
			.def(init<Shape>())
			.def(init<size_t>())
			.add_property("rank",shape_get_rank,shape_set_rank)
			.def("dim",shape_set_dimension)
			.def("dim",shape_get_dimension)
			.add_property("size",&Shape::size)
			.def("offset",&Shape::offset)
			.def("index",&Shape::index)
			.def(self == self)
			.def(self != self)
			//need some operators
			;
}

