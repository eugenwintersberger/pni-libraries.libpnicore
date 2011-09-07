/*
 * Scalar.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: eugen
 */

#ifndef SCALAR_HPP_
#define SCALAR_HPP_

#include <iostream>
#include <complex>

#include "PNITypes.hpp"
#include "ScalarObject.hpp"
#include "TypeInfo.hpp"
#include "Exceptions.hpp"
#include "ResultTypeTrait.hpp"

namespace pni {
namespace utils {


//! \ingroup Data-objects
//! \brief Scalar template for scalar values

//! Basically one can consider this as a concrete implementation of
//! the class ScalarObject. Along with all other attributes of a NumericObject
//! this template holds a single datum of an numeric type.
//! To make such a template useful it must not only provide support copy and
//! assignment operations, in addition full support for basic arithmetic operations
//! must be available.
//!
//! In connection with the Scalar object the assignment and conversion operator
//! need some special care.
//! The assignment operator comes in several flavors. Basically two cases
//! of assignment involving a Scalar<T> object must be considered
//! - an object of type Scalar<T> is assigned to an other object of type Scalar<U> where
//!   U is either the same as T or a different numeric type
//! - an object of type T is assigned to an object of type Scalar<U> where U is the same
//!   or a different type than T
//!
//! Thus, the assignment operator handles all cases where the Scalar object is
//! the l-value of an expression. Templates are used for cases where the r-value
//! of such an assignment expression is of different type. If the types do not
//! match exceptions are raised. In cases where two objects of type Scalar<T> are
//! assigned to each other not only the value but also the name, description, and
//! unit of the r-value object are transfered to the l-value object.
//!
//! An other situation is that the l-value of an expression is a simple variable
//! of native type T and the r-value an object of type Scalar<T>. This is
//! managed by the conversion operator. In cases where the type of the r-value and
//! the l-value differ there should be no problem as long as there is an implicit
//! conversion between the two types.
//!
//! A critical aspect of the Scalar<T> template are the arithmetic operations. All basic
//! operations (+,*,-,/) are supported. The unary version of these operations with an
//! object of Scalar<T> as an l-value are implemented as class members where the binary
//! versions are simple template functions. While for the former ones the type of the
//! result of the operation can be simply derived from the instance of the Scalar<T> object
//! The situation is not that easy for the binary function templates. These function
//! templates use fixed type selections where the result type is derived from the
//! argument types. This should avoid overflows during computation. The fact that a temporary
//! object of an appropriate type is created avoids us to implement complex tests to
//! determine whether or not an operation is allowed. However, in the end the result
//! is assigned to an object of a particular type. Thus, the temporary type and the
//! target type must be assignable - otherwise an exception will be thrown.
//! It is clear that for the binary versions of the arithmetic operators temporary objects
//! are created and returned by value. However, since the scalar objects are pretty small
//! this effort should not matter too much.
template<typename T> class Scalar: public ScalarObject {
private:
	T _value; //!< object holding the value of the Scalar object
public:
	typedef T DataType;
	typedef boost::shared_ptr<Scalar<T> > sptr;
	//! default constructor
	Scalar();
	//! copy constructor
	Scalar(const Scalar<T> &);
	//! constructor

	//! Constructor setting the value of the Scalar object.
	//! \param v value of type T
	Scalar(const T &v);
	//! constructor

	//! Constructor setting the value, name, and physical unit of the Scalar
	//! object.
	//! \param v value of type T
	//! \param n name of the object as String
	//! \param u unit of the object as String
	Scalar(const T &v, const String &n, const String &u);

	//! constructor

	//! Constructor setting the value, name, description, and physical unit of the Scalar
	//! object.
	//! \param v value of type T
	//! \param n name of the object as String
	//! \param u unit of the object as String
	//! \param d description of the object as String
	Scalar(const T &v, const String &n, const String &u, const String &d);
	//! constructor

	//! Constructor setting name and unit of the Scalar object.
	//! \param n name of the object as String
	//! \param u physical unit of the object as String
	Scalar(const String &n, const String &u);
	//! constructor

	//! Constructor setting name, description, and unit of the Scalar object.
	//! \param n name of the object as String
	//! \param u physical unit of the object as String
	//! \param d description of the object as String
	Scalar(const String &n, const String &u, const String &d);
	//! destructor
	virtual ~Scalar();


	//! assignment operator from a variable of type T

	//! Here a simple object of type T (in most cases this will be a native
	//! variable) is assigned to the _value member of a Scalar<T> object.
	//! This flavor of the assignment operator makes the usage of Scalar<T> objects
	//! easy - they behave just like normal variables. For cases where the r-value
	//! is not of type T there is no problem as long as there exists some implicit
	//! type conversion between T and the type of the variable.
	//! \param &v reference to a native variable of type T
	Scalar<T> &operator=(const T &v);
	template<typename U> Scalar<T> &operator=(const U &v);
	//! assignment operator from Scalar<T>

	//! This is the most trivial case. An object of type Scalar<T> is assigned
	//! to an other object of type Scalar<T>.
	Scalar<T> &operator=(const Scalar<T> &v);

	//! assignment operator from a Scalar<U> to Scalar<T>

	//! The most complex situation of assignment - an object of Scalar<U> is
	//! assigned to an object of Scalar<T> where U and T are different types.
	//! The template method performs type checking in order to figure out
	//! if the types are compatible or not at runtime and raises an exception
	//! if this is not the case.
	//! \throws TypeError thrown if U cannot be assigned to T
	//! \param v reference to an object of type Scalar<U>
	template <typename U> Scalar<T> &operator=(const Scalar<U> &v);

	//! conversion operator (read-only)

	//! The conversion operator handles cases where an object of type Scalar<T> is
	//! the r-value of an assignment expression while the l-value is a simple
	//! variable of type T. If the l-value is not of type T there should be no
	//! problem as long as there is an explicit conversion between the T and the
	//! type of the l-value variable.
	//!
	//! This implementation of the conversion operator returns the value of
	//! a scalar object. Thus, it cannot be used to alter the content of  the
	//! object.

	operator T() const{
		std::cout<<"native conversion operator!"<<std::endl;

		return _value;
	}

	template<typename U> operator U() const {
		std::cout<<"template conversion operator!"<<std::endl;

		return (U)_value;
	}

	//! return the value of a Scalar object

	//! Returns the value stored in the scalar Object. Since the value is returns
	//! this method cannot be used to alter the content of a Scalar object.
	//! Since we can use the conversion operator for the same purpose this
	//! method was implemented just for convenience and might be useful if a
	//! pointer to a scalar object is used.
	//! \return value of the Scalar object
	T getValue() const {
		return _value;
	}

	//! set value from scalar object

	//! Sets the value of the object from an other object of type Scalar<T>.
	//! No type checking is needed in this case because the objects are of same type.
	//! Unlike the assignment operator only the value of the two Scalar<T> objects
	//! are equal afer a call to this method. All other attributes of the class
	//! remain the same.
	//! \param v reference to the object from which the value should be taken
	void setValue(const Scalar<T> &v);
	//! set value from variable

	//! Sets the value of the object from a variable of type T. Since the variable
	//! is of same data type than the template type of the scalar object no type
	//! checking is needed. This method does the same as the corresponding
	//! assignment operator.
	//! \see Scalar<T> &operator=(const T &v)
	//! \param v reference to a variable of type T
	void setValue(const T &v);

	//! template to set the value of a Scalar

	//! Template method to set the value of a Scalar object
	//! from a Scalar object of different type. This method is
	//! useful if only a pointer exists to a Scalar<T> object
	//! and therefore the = operator cannot be called in an easy manner.
	//! \param &v reference to a Scalar object of type U
	template<typename U> void setValue(const Scalar<U> &v);
	//! template to set the value of a Scalar

	//! Template method to set the value of a Scalar object
	//! from a native variable of type U. This method is particularly
	//! useful if only a pointer to a Scalar<T> object exists
	//! and the = operator cannot be called in a simple manner.
	//! \param &v reference to a variable of type U
	template<typename U> void setValue(const U &v);

	//for each of the arithmetic operators three cases must be
	//taken into account:
	//1.) Scalar .Op. T
	//2.) T .Op. Scalar
	//3.) Scalar .Op. Scalar
	//in all cases the result will be of type Scalar.
	//this is no problem even if the result will be assigned to an
	//object of type T (in this case the conversion operator
	//does the job).


	//overload combind arithmetics and assignment operators
	//! unary and inplace / operator for Scalar<T> /= T
	Scalar<T> &operator/=(const T &v);
	template<typename U> Scalar<T> &operator/=(const U &v);
	//! unary and inplace / operator for Scalar<T> /= Scalar<T>
	Scalar<T> &operator/=(const Scalar<T> &v);
	template<typename U> Scalar<T> &operator/=(const Scalar<U> &v);
	//! unary and inplace + operator for Scalar<T> += T
	Scalar<T> &operator+=(const T &v);
	template<typename U> Scalar<T> &operator+=(const U &v);
	//! unary and inplace + operator for Scalar<T> += Scalar<T>
	Scalar<T> &operator+=(const Scalar<T> &v);
	template<typename U> Scalar<T> &operator+=(const Scalar<U> &v);
	//! unary and inplace - operator for Scalar<T> -= T
	Scalar<T> &operator-=(const T &v);
	template<typename U> Scalar<T> &operator-=(const U &v);
	//! unary and inplace - operator for Scalar<T> -= Scalar<T>
	Scalar<T> &operator-=(const Scalar<T> &v);
	template<typename U> Scalar<T> &operator-=(const Scalar<U> &v);
	//! unary and inplace * operator for Scalar<T> *= T
	Scalar<T> &operator*=(const T &v);
	template<typename U> Scalar<T> &operator*=(const U &v);
	//! unary and inplace * operator for Scalar<T> *= Scalar<T>
	Scalar<T> &operator*=(const Scalar<T> &v);
	template<typename U> Scalar<T> &operator*=(const Scalar<U> &v);

	//! get a void pointer to the data
	virtual void *getVoidPtr(){
		return (void *)(&_value);
	}

	//return the type numeric ID of the Scalar<T> object
	virtual PNITypeID getTypeID() const{
		return PNITypeInfo<T>::TypeID;
	}

};

//======================Constructors and destructors=======================================
//default constructor
template<typename T> Scalar<T>::Scalar() :
	ScalarObject() {
	_value = 0;
}

template<typename T> Scalar<T>::Scalar(const Scalar<T> &s) :
	ScalarObject(s) {
	_value = s._value;
}

template<typename T> Scalar<T>::Scalar(const T &v) :
	ScalarObject() {
	_value = v;
}

template<typename T> Scalar<T>::Scalar(const T &v, const String &n,
		const String &u) :
	ScalarObject(n, u) {
	_value = v;
}

template<typename T> Scalar<T>::Scalar(const T &v, const String &n,
		const String &u, const String &d) :
	ScalarObject(n, u, d) {
	_value = v;
}


template<typename T> Scalar<T>::Scalar(const String &n, const String &u) :
	ScalarObject(n, u) {
	_value = 0;
}

template<typename T> Scalar<T>::Scalar(const String &n, const String &u,
		const String &d) :
	ScalarObject(n, u, d) {
	_value = 0;
}

template<typename T> Scalar<T>::~Scalar() {
	_value = 0;
}

//==========methods for accessing the data of a scalar in a typesafe way===================
template<typename T> void Scalar<T>::setValue(const T &v){
	_value = v;
}
template<typename T> void Scalar<T>::setValue(const Scalar<T> &v){
	EXCEPTION_SETUP("template<typename T> void Scalar<T>::setValue(const Scalar<T> &v)");

	setValue(v.getValue());
}

template<typename T> template<typename U> void Scalar<T>::setValue(const U &v){
	EXCEPTION_SETUP("template<typename T> template<typename U> void Scalar<T>::setValue(const U &v)");

	try{
		TypeInfo<T>::isCompatibleForAssignment(v);
	}catch(...){
		EXCEPTION_INIT(TypeError,"Cannot assign value due to incompatible types!");
		EXCEPTION_THROW();
	}

	_value = (T)v;

}

template<typename T> template<typename U> void Scalar<T>::setValue(const Scalar<U> &s){
	EXCEPTION_SETUP("template<typename T> template<typename U> void Scalar<T>::setValue(const Scalar<U> &s)");

	try{
		setValue(s.getValue());
	}catch(...){
		EXCEPTION_INIT(TypeError,"Cannot assign values!");
		EXCEPTION_THROW();
	}
}

//======================unary arithmetic operators=========================================
template<typename T> Scalar<T>& Scalar<T>::operator/=(const T &v) {
	//everything the same type - we have to do nothing
	_value /= v;
	return *this;
}

template<typename T>
template<typename U> Scalar<T>& Scalar<T>::operator/=(const U &v) {
	EXCEPTION_SETUP("template<typename T> template<typename U> Scalar<T>& Scalar<T>::operator/=(const U &v)");



	_value /= (T)v;
	return *this;
}

template<typename T> Scalar<T>& Scalar<T>::operator/=(const Scalar<T> &v) {
	_value /= v._value;
	return *this;
}

template<typename T>
template<typename U> Scalar<T>& Scalar<T>::operator/=(const Scalar<U> &v){
	EXCEPTION_SETUP("template<typename T> template<typename U> Scalar<T>& Scalar<T>::operator/=(const Scalar<U> &v)");

	_value /= (T)v.getValue();
	return *this;
}

template<typename T> Scalar<T>& Scalar<T>::operator+=(const T &v) {
	_value += v;
	return *this;
}

template<typename T>
template<typename U> Scalar<T> &Scalar<T>::operator+=(const U &v){
	EXCEPTION_SETUP("template<typename T> template<typename U> Scalar<T> &Scalar<T>::operator+=(const U &v)");

	//what happens if we want to add a signed integer to an unsigned integer
	if((!TypeInfo<T>::isSigned())&&(TypeInfo<U>::isSigned())){
		if((v<0)&&((-v)>_value)){
			EXCEPTION_INIT(RangeError,"You cannot add a negative integer to an unsigned "
									  "one if its absolute value is larger than that of the unsigned one!");
			EXCEPTION_THROW();
		}
	}

	//you cannot add a float to an integer
	if((TypeInfo<T>::isInteger())&&(!TypeInfo<U>::isInteger())){
		EXCEPTION_INIT(TypeError,"You cannot add a float to an integer!");
		EXCEPTION_THROW();
	}

	_value += v;
	return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator+=(const Scalar<T> &v) {
	_value += v.getValue();
	return *this;
}

template<typename T>
template<typename U> Scalar<T> &Scalar<T>::operator+=(const Scalar<U> &v){
	EXCEPTION_SETUP("template<typename T> template<typename U> Scalar<T> &Scalar<T>::operator+=(const Scalar<U> &v)");

	//what happens if we want to add a signed integer to an unsigned integer
	if((!TypeInfo<T>::isSigned())&&(TypeInfo<U>::isSigned())){
		if((v.getValue()<0)&&((-v.getValue())>_value)){
			EXCEPTION_INIT(RangeError,"You cannot add a negative integer to an unsigned "
									  "one if its absolute value is larger than that of the unsigned one!");
			EXCEPTION_THROW();
		}
	}

	//you cannot add a float to an integer
	if((TypeInfo<T>::isInteger())&&(!TypeInfo<U>::isInteger())){
		EXCEPTION_INIT(TypeError,"You cannot add a float to an integer!");
		EXCEPTION_THROW();
	}

	_value += (T)v.getValue();
	return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator-=(const T &v) {
	_value -= v;
	return *this;
}

template<typename T>
template<typename U> Scalar<T> &Scalar<T>::operator-=(const U &v){
	EXCEPTION_SETUP("template<typename T> template<typename U> Scalar<T> &Scalar<T>::operator-=(const U &v)");
	_value -= (T)v;
	return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator-=(const Scalar<T> &v) {
	_value -= v;
	return *this;
}

template<typename T>
template<typename U> Scalar<T> &Scalar<T>::operator-=(const Scalar<U> &v){
	EXCEPTION_SETUP("template<typename T> template<typename U> Scalar<T> &Scalar<T>::operator-=(const Scalar<U> &v)");

	_value = (T)v.getValue();
	return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator*=(const T &v) {
	_value *= v;
	return *this;
}

template<typename T>
template<typename U> Scalar<T> &Scalar<T>::operator*=(const U &v){
	EXCEPTION_SETUP("template<typename T> template<typename U> Scalar<T> &Scalar<T>::operator*=(const U &v)");

	_value *= (T)v;
	return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator*=(const Scalar<T> &v) {
	_value *= v;
	return *this;
}

template<typename T>
template<typename U> Scalar<T> &Scalar<T>::operator*=(const Scalar<U> &v){
	EXCEPTION_SETUP("template<typename T> template<typename U> Scalar<T> &Scalar<T>::operator*=(const Scalar<U> &v)");

	_value *= (T)v.getValue();
	return *this;
}

//=======================comparison operator=================================
template<typename T> bool operator==(const Scalar<T> &a, const Scalar<T> &b) {
	return (a.getValue() == b.getValue());
}

template<typename T> bool operator==(const T& a, const Scalar<T> &b) {
	return (a == b.getValue());
}

template<typename T> bool operator==(const Scalar<T> &a, const T& b) {
	return (a.getValue() == b);
}

template<typename T> bool operator!=(const Scalar<T> &a,const Scalar<T> &b){
	if(a == b) return false;
	return true;
}

template<typename T> bool operator!=(const T &a,const Scalar<T> &b){
	if(a == b) return false;
	return true;
}

template<typename T> bool operator!=(const Scalar<T> &a,const T &b){
	if(a == b) return false;
	return true;
}

//overloaded output operator
template<typename T> std::ostream &operator<<(std::ostream &o,
		const Scalar<T> &v) {

	if(v.getName()!=""){
		o<<v.getName()<<" = ";
	}
	o << v.getValue();
	if(v.getUnit() != ""){
		o<<" "<<v.getUnit();
	}

	if(v.getDescription()!=""){
		o<<" ("<<v.getDescription()<<")";
	}

	return o;
}

//overloaded assignment operators - these operators must be class members
template<typename T> Scalar<T> &Scalar<T>::operator=(const T &v) {
	//std::cout<<"native variable assignment!"<<std::endl;
	_value = v;
	return *this;
}

template<typename T>
template<typename U> Scalar<T> &Scalar<T>::operator=(const U &v){
	EXCEPTION_SETUP("template<typename T> template<typename U> Scalar<T> &Scalar<T>::operator(const U &v)");

	try{
		TypeInfo<T>::isCompatibleForAssignment(v);
	}catch(...){
		EXCEPTION_INIT(TypeError,"Cannot assign value to scalar due to incompatible types!");
		EXCEPTION_THROW();
	}

	//std::cout<<"template variable assignment!";
	_value = (T)v;

	return *this;
}

template<typename T>
template<typename U> Scalar<T> &Scalar<T>::operator=(const Scalar<U> &v){
	EXCEPTION_SETUP("template<typename T> template<typename U> Scalar<T> &"
					 "Scalar<T>::operator=(const Scalar<U> &v)");
	//check if assignment is possible
	std::cout<<"template assignment of scalar objects!"<<std::endl;
	if((void *)this != (void *)(&v)){
		try{
			TypeInfo<T>::isCompatibleForAssignment(v.getValue());
		}catch(...){
			EXCEPTION_INIT(TypeError,"Cannot assign types!");
			EXCEPTION_THROW();
		}

		//set all parameters
		NumericObject &this_o = (NumericObject &)(*this);
		NumericObject &that_o = (NumericObject &)v;
		this_o = that_o;

		//now we have to transfer the value
		setValue(v.getValue());
	}

	return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator=(const Scalar<T> &s){
	std::cout<<"native assignment of scalar objects!"<<std::endl;
	if(this != &s){
		(*this).setValue(s.getValue());
		(*this).setName(s.getName());
		(*this).setUnit(s.getUnit());
		(*this).setDescription(s.getDescription());
	}
	return *this;
}

//===================binary arithmetic operators====================================

//! binary add operation
template<typename A,typename B>
const Scalar<typename ResultTypeTrait<A,B>::AddResultType > operator+(const Scalar<A> &a,const Scalar<B> &b){
	std::cout<<"template binary operator + Scalar Scalar"<<std::endl;
	Scalar<typename ResultTypeTrait<A,B>::AddResultType > o;

	o.setValue((typename ResultTypeTrait<A,B>::AddResultType)(a.getValue()+b.getValue()));

	return o;
}

template<typename A,typename B>
const Scalar<typename ResultTypeTrait<A,B>::AddResultType > operator+(const Scalar<A> &a,const B &b){
	Scalar<typename ResultTypeTrait<A,B>::AddResultType > o;

	o.setValue((typename ResultTypeTrait<A,B>::AddResultType)(a.getValue()+b));
	return o;
}

template<typename A,typename B>
const Scalar<typename ResultTypeTrait<A,B>::AddResultType > operator+(const A &a,const Scalar<B> &b){
	Scalar<typename ResultTypeTrait<A,B>::AddResultType > o;

	o.setValue((typename ResultTypeTrait<A,B>::AddResultType)(a+b.getValue()));

	return o;
}

//overloaded subtraction operator
template<typename A,typename B>
const Scalar<typename ResultTypeTrait<A,B>::SubResultType > operator-(const Scalar<A> &a, const Scalar<B> &b) {
	Scalar<typename ResultTypeTrait<A,B>::SubResultType > tmp;

	tmp.setValue((typename ResultTypeTrait<A,B>::SubResultType)(a.getValue()-b.getValue()));

	return tmp;
}

template<typename A,typename B>
const Scalar<typename ResultTypeTrait<A,B>::SubResultType > operator-(const A& a, const Scalar<B> &b) {
	Scalar<typename ResultTypeTrait<A,B>::SubResultType > tmp;

	tmp.setValue((typename ResultTypeTrait<A,B>::SubResulType)(a-b.getValue()));

	return tmp;
}

template<typename A,typename B>
const Scalar<typename ResultTypeTrait<A,B>::SubResultType > operator-(const Scalar<A> &a, const B &b) {
	Scalar<typename ResultTypeTrait<A,B>::SubResultType > tmp;

	tmp.setValue((typename ResultTypeTrait<A,B>::SubResultType)(a.getValue()-b));
	return tmp;
}

//overloading the multiplication operator
template<typename A,typename B>
const Scalar<typename ResultTypeTrait<A,B>::MultResultType > operator*(const Scalar<A> &a, const Scalar<B> &b) {
	Scalar<typename ResultTypeTrait<A,B>::MultResultType > tmp;

	tmp.setValue((typename ResultTypeTrait<A,B>::MultResultType)(a.getValue()*b.getValue()));
	return tmp;
}

template<typename A,typename B>
const Scalar<typename ResultTypeTrait<A,B>::MultResultType > operator*(const A& a, const Scalar<B> &b) {
	Scalar<typename ResultTypeTrait<A,B>::MultResultType > tmp;

	tmp.setValue((typename ResultTypeTrait<A,B>::MultResultType)(a*b.getValue()));
	return tmp;
}

template<typename A,typename B>
const Scalar<typename ResultTypeTrait<A,B>::MultResultType > operator*(const Scalar<A> &a, const B& b) {
	Scalar<typename ResultTypeTrait<A,B>::MultResultType > tmp;

	tmp.setValue((typename ResultTypeTrait<A,B>::MultResultType)(a.getValue()*b));
	return tmp;
}

//overloading the division operator
template<typename A,typename B>
const Scalar<typename ResultTypeTrait<A,B>::DivResultType > operator/(const Scalar<A> &a, const Scalar<B> &b) {
	Scalar<typename ResultTypeTrait<A,B>::DivResultType > tmp;

	tmp.setValue((typeof ResultTypeTrait<A,B>::DivResultType)(a.getValue()/b.getValue()));
	return tmp;
}

template<typename A,typename B>
const Scalar<typename ResultTypeTrait<A,B>::DivResultType > operator/(const A& a, const Scalar<B> &b) {
	Scalar<typename ResultTypeTrait<A,B>::DivResultType > tmp;

	tmp.setValue((typename ResultTypeTrait<A,B>::DivResultType)(a/b.getValue()));
	return tmp;
}

template<typename A,typename B>
const Scalar<typename ResultTypeTrait<A,B>::DivResultType > operator/(const Scalar<A> &a, const B &b) {
	Scalar<typename ResultTypeTrait<A,B>::DivResultType > tmp;

	tmp.setValue((typename ResultTypeTrait<A,B>::DivResultType)(a.getValue()/b));
	return tmp;
}

//declare some useful default types
typedef Scalar<Int8>   Int8Scalar;
typedef Scalar<UInt8>  UInt8Scalar;
typedef Scalar<Int16>  Int16Scalar;
typedef Scalar<UInt16> UInt16Scalar;
typedef Scalar<Int32>  Int32Scalar;
typedef Scalar<UInt32> UInt32Scalar;
typedef Scalar<Int64>  Int64Scalar;
typedef Scalar<UInt64> UInt64Scalar;

typedef Scalar<Float32>  Float32Scalar;
typedef Scalar<Float64>  Float64Scalar;
typedef Scalar<Float128> Float128Scalar;

typedef Scalar<std::complex<Float32> >  Complex32Scalar;
typedef Scalar<std::complex<Float64> >  Complex64Scalar;
typedef Scalar<std::complex<Float128> > Complex128Scalar;

//end of namespace
}
}

#endif /* SCALAR_HPP_ */
