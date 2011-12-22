/*
 * DataObject.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: Eugen Wintersberger
 */

extern "C"{
    #include<Python.h>
}

#include <boost/python.hpp>
#include <iostream>


#include "../src/DataObject.hpp"
#include "../src/NumericObject.hpp"
#include "../src/ArrayObject.hpp"
#include "../src/Types.hpp"
#include "../src/Shape.hpp"
#include "../src/Buffer.hpp"
#include "../src/Index.hpp"
#include "../src/Scalar.hpp"
#include "../src/ArrayObject.hpp"
#include "../src/Array.hpp"
#include "../src/Exceptions.hpp"

using namespace pni::utils;
using namespace boost::python;

void wrap_numeric_object();
void wrap_data_object();
void wrap_index();
void wrap_shape();
void wrap_buffer();
void wrap_scalar();
void wrap_array();



//=====================translate exceptions=====================================
void index_error_translator(IndexError const &error){
    PyErr_SetString(PyExc_UserWarning,"IndexError raised by C++ code!");
}

void MemoryAllocationError_translator(MemoryAllocationError const &error){
    PyErr_SetString(PyExc_UserWarning,"MemoryAllocationError raised by C++ code!");
}

void ShapeMissmatchError_translator(ShapeMissmatchError const &error){
    PyErr_SetString(PyExc_UserWarning,"ShapeMissmatchError raised by C++ code!");
}

void SizeMissmatchError_translator(SizeMissmatchError const &error){
    PyErr_SetString(PyExc_UserWarning,"SizeMissmatchError raised by C++ code!");
}

void KeyError_translator(KeyError const &error){
    PyErr_SetString(PyExc_UserWarning,"KeyError raised by C++ code!");
}

void FileError_translator(FileError const &error){
    PyErr_SetString(PyExc_UserWarning,"FileError raised by C++ code!");
}

void TypeError_translator(TypeError const &error){
    PyErr_SetString(PyExc_UserWarning,"TypeError raised by C++ code!");
}

void RangeError_translator(RangeError const &error){
    PyErr_SetString(PyExc_UserWarning,"RangeError raised by C++ code!");
}

void MemoryAccessError_translator(MemoryAccessError const &error){
    PyErr_SetString(PyExc_UserWarning,"MemoryAccessError raised by C++ code!");
}

void ProcessingError_translator(ProcessingError const &error){
    PyErr_SetString(PyExc_UserWarning,"ProcessingError raised by C++ code!");
}

void AssignmentError_translator(AssignmentError const &error){
    PyErr_SetString(PyExc_UserWarning,"AssignmentError raised by C++ code!");
}


BOOST_PYTHON_MODULE(pniutils)
{

    //===================register exception translators=========================
    register_exception_translator<IndexError>(index_error_translator);
    register_exception_translator<MemoryAllocationError>(MemoryAllocationError_translator);
    register_exception_translator<ShapeMissmatchError>(ShapeMissmatchError_translator);
    register_exception_translator<SizeMissmatchError>(SizeMissmatchError_translator);
    register_exception_translator<KeyError>(KeyError_translator);
    register_exception_translator<FileError>(FileError_translator);
    register_exception_translator<TypeError>(TypeError_translator);
    register_exception_translator<RangeError>(RangeError_translator);
    register_exception_translator<MemoryAccessError>(MemoryAccessError_translator);
    register_exception_translator<ProcessingError>(ProcessingError_translator);
    register_exception_translator<AssignmentError>(AssignmentError_translator);

	//===============Wrap TypeID enum class=====================================
	enum_<TypeID>("TypeID")
			.value("NONE",TypeID::NONE)
			.value("UINT8",TypeID::UINT8)
			.value("INT8",TypeID::INT8)
			.value("UINT16",TypeID::UINT16)
			.value("INT16",TypeID::INT16)
			.value("UINT32",TypeID::UINT32)
			.value("INT32",TypeID::INT32)
			.value("UINT64",TypeID::UINT64)
			.value("INT64",TypeID::INT64)
			.value("FLOAT32",TypeID::FLOAT32)
			.value("FLOAT64",TypeID::FLOAT64)
			.value("FLOAT128",TypeID::FLOAT128)
			.value("COMPLEX32",TypeID::COMPLEX32)
			.value("COMPLEX64",TypeID::COMPLEX64)
			.value("COMPLEX128",TypeID::COMPLEX128)
			.value("STRING",TypeID::STRING)
			.value("BINARY",TypeID::BINARY)
			.value("BOOLEAN",TypeID::BOOLEAN)
			;

	//==================Wrap TypeClass enum class===============================
	enum_<TypeClass>("TypeClass")
			.value("NONE",TypeClass::NONE)
			.value("INTEGER",TypeClass::INTEGER)
			.value("FLOAT",TypeClass::FLOAT)
			.value("BINARY",TypeClass::BINARY)
			.value("BOOL",TypeClass::BOOL)
			.value("COMPLEX",TypeClass::COMPLEX)
			;


    wrap_data_object();
    wrap_numeric_object();
    wrap_index();
    wrap_shape();
    wrap_buffer();
    wrap_scalar();
    wrap_array();

}




