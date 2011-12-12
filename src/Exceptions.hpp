/*
 * Declaration exception classes and related macros
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Declaration of the exception classes provided by the library along with
 * some macros that make using exceptions easier.
 *
 * Created on: Apr 19, 2011
 *     Author: Eugen Wintersberger
 *
 */

#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__

#include<iostream>
#include<string>

#include "Exceptions.hpp"
#include "Types.hpp"

namespace pni{
namespace utils{

//================Macros related to exceptions==================================

//Macro for setting up exceptions at the very begin of a function or method
#define EXCEPTION_SETUP(issuer) \
	static String __ExIssuer = (issuer);\
	String __ExDescription

//Macro called directly before an exception is called it sets up the
//exception which will be thrown
#define EXCEPTION_INIT(extype,exdesc)\
	extype __error;\
	__ExDescription = (exdesc);\
	__error.name(__ExIssuer);\
	__error.description(__ExDescription);


//Throw an exception
#define EXCEPTION_THROW()\
	std::cerr<<__error<<std::endl;\
	std::cerr<<"in line: "<<__LINE__<<" of file "<<__FILE__<<std::endl<<std::endl;\
	throw __error;


//========================Exception classes=====================================

//! \defgroup Exceptions
//! Exception object used throughout the library for Error handling.

//! \ingroup Exceptions
//! \brief Exceptions base class

//! The base class for all exceptions in the library. Constructors are design
//! to take either const char * values or const std::string references as
//! valid input arguments. This should provide maximum flexibility in exception
//! creation.
class Exception{
private:
	String _name; //!< name of the exception
	String _issuer; //!< issuer of the exception
	String _description; //!< description of the error occured
protected:
	std::ostream &print(std::ostream &) const;
public:
	//! default constructor
	Exception() {
	}
	//! constructor with name as string

	//! \param n name of the exception
	Exception(const String &n);
	//! constructor with name and source as string objects

	//! \param n name of the exception
	//! \param i name or ID or the exceptions issuer
	Exception(const String &n, const String &i);
	//! constructor with name, source, and description as string

	//! \param n name of the exception
	//! \param w name or ID of the exceptions issuer
	//! \param d description of the exception
	Exception(const String &n, const String &w, const String &d);
	//! virtual destructor
	virtual ~Exception() {
	}

	//! set the exception name

	//! \param name exception name
	void name(const std::string &name) {
		_name = name;
	}
	//! get the exceptions name

	//! \return reference to the string object holding the name
	const String &name() const {
		return _name;
	}

	//! set the exception issuer

	//! \param i name or some ID of the issuer
	void issuer(const String &i) {
		_issuer = i;
	}
	//! get the exceptions issuer

	//! \return reference to the string object with the exceptions ID or name
	const String &issuer() const {
		return _issuer;
	}

	//! set exception desccription

	//! \param desc description of the exception
	void description(const std::string &desc) {
		_description = desc;
	}
	//! get the exceptions description

	//! \return reference to the string object with the exceptions description
	const String &description() const {
		return _description;
	}

	//! output operator for exceptions
	friend std::ostream &operator<<(std::ostream &, const Exception &);
        
};


//------------------------------------------------------------------------------
//! \ingroup Exceptions
//! \brief memory allocation error

//! This exception is typically raised if memory allocation fails. In other
//! words if a call of the new operator returns NULL.
class MemoryAllocationError: public Exception {
public:
	//! default constructor
	MemoryAllocationError() :
		Exception("MemoryAllocationError") {
	}
	//! constructor

	//! \param i name or ID of the exceptions issuer
	//! \param d description of the exception
	MemoryAllocationError(const String &i, const String &d) :
		Exception("MemoryAllocationError", i, d) {
	}
	//! destructor
	virtual ~MemoryAllocationError() {
	}

	friend std::ostream &operator<<(std::ostream &o,const MemoryAllocationError &e);
};

//------------------------------------------------------------------------------
//! \ingroup Exceptions
//! \brief Shape mismatch error

//! This exception is usually raised in cases where array operations require
//! shape matching of the involved arrays but their shapes are different.
class ShapeMissmatchError: public Exception {
public:
	//! default constructor
	ShapeMissmatchError() :
		Exception("ArrayShapeMissmatchError") {
	}
	//! constructor

	//! \param i name or ID of the exceptions issuer
	//! \param d description of the exception
	ShapeMissmatchError(const String &i, const String &d) :
		Exception("ArrayShapeMissmatchError", i, d) {
	}

	//! destructor
	virtual ~ShapeMissmatchError() {
	}

	friend std::ostream &operator<<(std::ostream &o,const ShapeMissmatchError &e);
};

//------------------------------------------------------------------------------
//! \ingroup Exceptions
//! \brief Size missmatch error

//! This exception will be raised in cases where buffer sizes do not meet the
//! requirements. A typical situation would be that a buffer is passed to an
//! Array object whose size does not match the size given by the ArrayShape
//! object of the Array.
class SizeMissmatchError: public Exception {
public:
	//! default constructor
	SizeMissmatchError() :
		Exception("SizeMissmatchError") {
	}
	//! constructor

	//! \param i name or ID of the exception issuer
	//! \param d description of the exception
	SizeMissmatchError(const String &i, const std::string &d) :
		Exception("SizeMissmatchError", i, d) {
	}

	//! destructor
	virtual ~SizeMissmatchError() {
	}

	friend std::ostream &operator<<(std::ostream &o,const SizeMissmatchError &e);
};

//------------------------------------------------------------------------------
//! \ingroup Exceptions
//! \brief index error

//! Raised typically in cases where the [] operator is used to access a data
//! element but the provided index goes beyond the address space of the buffer
//! or array.
class IndexError: public Exception {
public:
	//! default constructor
	IndexError() :
		Exception("IndexError") {
	}
	//! constructor

	//! \param i name or ID of the exceptions issuer
	//! \param d description of the exception
	IndexError(const String &i, const String &d) :
		Exception("IndexError", i, d) {
	}
	//! destructor
	virtual ~IndexError() {
	}

	friend std::ostream &operator<<(std::ostream &o,const IndexError &e);
};

//------------------------------------------------------------------------------
//! \ingroup Exceptions
//! \brief key exception

//! Raised in cases where a problem with the key of a hash map.
class KeyError: public Exception{
public:
	//! default constructor
	KeyError():Exception("KeyError"){}
	//! constructor

	//! \param i signature of the expcetion issuer
	//! \param d description of the error
	KeyError(const String &i,const String &d):Exception("KeyError",i,d){}
	//! destructor
	virtual ~KeyError(){}

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const KeyError &e);
};

//------------------------------------------------------------------------------
//! \ingroup Exceptions
//! \brief indicates file IO problems

//! Raised typically in case of File IO problems
class FileError: public Exception {
public:
	//! default constructor
	FileError() :
		Exception("FileError") {
	}
	//! constructor

	//! \param i name or ID of the exception issuer
	//! \param d description of the exception
	FileError(const String &i, const String &d) :
		Exception("FileError", i, d) {
	}

	//! destructor
	virtual ~FileError() {
	}

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const FileError &e);

};

//------------------------------------------------------------------------------
//! \ingroup Exceptions
//! \brief data type errors

//! This exception is raised in cases of data type errors.
class TypeError: public Exception {
public:
	//! default constructor
	TypeError() :
		Exception("TypeError") {
	}
	//! constructor

	//! Constructor setting source and description of the error
	//! \param w error source as String
	//! \param i error description as String
	TypeError(const String &i, const String &d) :
		Exception("TypeError", i, d) {
	}
	//! destructor
	virtual ~TypeError() {
	}

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const TypeError &e);
};

//------------------------------------------------------------------------------
//! \ingroup Exceptions
//! \brief data range error

//! This exception is raised in cases where data values exceed the range
//! spanned by their data type.
class RangeError: public Exception {
public:
	//! default constructor
	RangeError():
		Exception("RangeError"){
	}

	//! constructor

	//! Constructor setting source and description of the error
	//! \param i error issuer as string
	//! \param d error description as string
	RangeError(const String &i,const String &d):
		Exception("RangeError",i,d){
	}

	//! destructor
	virtual ~RangeError(){
	}

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const RangeError &e);
};

//------------------------------------------------------------------------------
//! \ingroup Exceptions
//! \brief not implemented exception

//! This exception can be used to mark methods of abstract or base classes
//! as not implemented. Such an approach can be quite usefull for debugging
//! and development.
class NotImplementedError:public Exception{
public:
	//! default construtor
	NotImplementedError():
		Exception("NotImplementedError"){
	}

	//! constructor

	//! Constructor setting source and description of the error
	//! \param i issuer of the exception
	//! \param d error description
	NotImplementedError(const String &i,const String &d):
		Exception("NotImplementedError",i,d){
	}

	//! destructor
	virtual ~NotImplementedError(){
	}

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const NotImplementedError &e);
};

//------------------------------------------------------------------------------
//! \ingroup Exceptions
//! \brief for access to not allocated memory

//! This exception will be thrown in cases where a user wants to access
//! data and no memory has been allocated.
class MemoryAccessError:public Exception{
public:
	//! default constructor
	MemoryAccessError():Exception("MemoryAccessError"){
	}

	//! constructor

	//! Constructor setting the issuer and description of the error.
	//! \param i issuer fo the exception
	//! \param d error description
	MemoryAccessError(const String &i,const String &d):
		Exception("MemoryAccessError",i,d){
	}

	//! destructor
	virtual ~MemoryAccessError(){
	}

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const MemoryAccessError &e);
};

//------------------------------------------------------------------------------
//! \ingroup Exceptions
//! \brief error during processing

//! This exception will be thrown in basically all cases where an error
//! occurs during some numerical calculations or other processing jobs.
class ProcessingError:public Exception{
public:
	//! default constructor
	ProcessingError():Exception("ProcessingError"){
	}

	//! constructor

	//! Constructor setting the issuer and description of the error.
	//! \param i issuer fo the exception
	//! \param d error description
	ProcessingError(const String &i,const String &d):
		Exception("ProcessingError",i,d){
	}

	//! destructor
	virtual ~ProcessingError(){
	}

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const ProcessingError &e);
};

//------------------------------------------------------------------------------
//! \ingroup Exceptions
//! \brief error during assignment

//! A very general exception thrown in case of any error during an assignment
//! operation.
class AssignmentError:public Exception{
public:
	//! default constructor
	AssignmentError():Exception("AssignmentError"){
	}

	//! constructor

	//! Constructor setting the issuer and description of the error.
	//! \param i issuer fo the exception
	//! \param d error description
	AssignmentError(const String &i,const String &d):
		Exception("AssignmentError",i,d){
	}

	//! destructor
	virtual ~AssignmentError(){

	}

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const AssignmentError &e);
};

}
}
#endif
