/*
 * Array.cpp
 *
 *  Created on: Dec 22, 2011
 *      Author: Eugen Wintersberger
 */




#include <boost/python.hpp>


#include "../src/Types.hpp"
#include "../src/BufferObject.hpp"
#include "../src/Array.hpp"


using namespace pni::utils;
using namespace boost::python;

template<typename T>
class ArrayWrapper{
    private:
        Array<T> _array;
        PyObject *_obj;

    public:
        ArrayWrapper(){

        }

        ArrayWrapper(const Shape &s){
            _array = Array<T>(s);
            _array.allocate();

            //need to allocate the numpy array now

        }

        virtual ~ArrayWrapper();

        String get_name() const{
            return _array.name();
        }

        void set_name(const String &n){
            _array.name(n);
        }

        String get_unit() const {
            return _array.unit();
        }

        void set_unit(const String &u){
            _array.unit(u);
        }

        String get_description() const {
            return _array.description();
        }

        void set_description(const String &d){
            _array.description(d);
        }

        


        
};


void wrap_array(){
	//================Wrapping the Array template===============================
	void (Array<Float64>::*set_buffer)(const BufferObject &) = &Array<Float64>::buffer;
	const BufferObject &(Array<Float64>::*get_buffer)() const = &Array<Float64>::buffer;
	void (Array<Float64>::*set_shape)(const Shape &) = &Array<Float64>::shape;
	const Shape &(Array<Float64>::*get_shape)() const = &Array<Float64>::shape;
	class_<Array<Float64> >("Float64Array")
			.def(init<>())
			.def(init<Array<Float64> >())
			.def(init<Shape>())
			.def(init<Shape,Buffer<Float64> >())
			.def(init<Shape,Buffer<Float64>,String,String,String>())
			.def(init<Shape,String,String,String>())

			.add_property("buffer",make_function(get_buffer,return_internal_reference<1>()),
					set_buffer)
			.add_property("shape",make_function(get_shape,return_internal_reference<1>()),set_shape)

            .def("allocate",&Array<Float64>::allocate)

            ;

}
