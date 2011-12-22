/*
 * Index.cpp
 *
 *  Created on: Dec 22, 2011
 *      Author: Eugen Wintersberger
 */




#include <boost/python.hpp>

#include "../src/Types.hpp"
#include "../src/Index.hpp"


using namespace pni::utils;
using namespace boost::python;

void wrap_index(){
	//========================Wrapping Index====================================
	size_t (Index::*index_get_rank)() const = &Index::rank;
	void   (Index::*index_set_rank)(size_t) = &Index::rank;
	class_<Index>("Index")
			.def(init<size_t>())
			.def(init<Index>())
			.add_property("rank",index_get_rank,index_set_rank)
			.def("get",&Index::get)
			.def("set",&Index::set)
			.def("inc",&Index::inc)
			.def("dec",&Index::dec)
			.def(self == self)
			.def(self != self)
			;

}


