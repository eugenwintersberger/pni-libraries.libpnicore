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

#include "ScalarObject.hpp"
#include "TypeInfo.hpp"
#include "Exceptions.hpp"

namespace pni {
namespace utils {

//this is the first part to make the friend declaration for templates for
//correctly - this code is just to imform the compiler!
template<typename T> class Scalar;
template<typename T> std::ostream &operator<<(std::ostream &o,
		const Scalar<T> &v);

template<typename T> Scalar<T>
		operator+(const Scalar<T> &a, const Scalar<T> &b);
template<typename T> Scalar<T> operator+(const T& a, const Scalar<T> &b);
template<typename T> Scalar<T> operator+(const Scalar<T> &a, const T&b);

template<typename T> Scalar<T>
		operator-(const Scalar<T> &a, const Scalar<T> &b);
template<typename T> Scalar<T> operator-(const T& a, const Scalar<T> &b);
template<typename T> Scalar<T> operator-(const Scalar<T> &a, const T &b);

template<typename T> Scalar<T>
		operator*(const Scalar<T> &a, const Scalar<T> &b);
template<typename T> Scalar<T> operator*(const T& a, const Scalar<T> &b);
template<typename T> Scalar<T> operator*(const Scalar<T> &a, const T& b);

template<typename T> Scalar<T>
		operator/(const Scalar<T> &a, const Scalar<T> &b);
template<typename T> Scalar<T> operator/(const T& a, const Scalar<T> &b);
template<typename T> Scalar<T> operator/(const Scalar<T> &a, const T &b);

template<typename T> bool operator==(const Scalar<T> &a, const Scalar<T> &b);
template<typename T> bool operator==(const T& a, const Scalar<T> &b);
template<typename T> bool operator==(const Scalar<T> &a, const T& b);

//! \ingroup Data-objects
//! \brief Scalar template for scalar values

//! Basically one can consider this as a concrete implementation of
//! the class ScalarObject. Along with all other attributes of a NumericObject
//! this template holds data in a single (scalar) value.
//!
//! To make such a template useful it must not only provide support copy and
//! assignment operations, in addition full support for basic arithmetic operations
//! must be available.
template<typename T> class Scalar: public ScalarObject {
private:
	//method raises an exception if the two types are not compatible
	template<typename U> void _type_is_compatible(const U &v) const;
protected:
	T _value; //!< object holding the value of the Scalar object
public:
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


	//for the assignment operator two cases must be considered
	//1.) An object of type Scalar is assigned to a Scalar instance
	//2.) An object of type T is assigned to a Scalar instance
	//basically the assignment operator handles cases where the Scalar object
	//is an l-value of an expression.
	//What is still missing here is the case that the r-value of the
	//expression is of different type than T. This case still requires
	//handling to avoid problems later on.

	//! assignment operator from a variable of type T

	//! Here a simple object of type T (in most cases this will be a native
	//! variable) is assigned to the _value member of a Scalar<T> object.
	//! This flavor of the assignment operator makes the usage of Scalar<T> objects
	//! easy - they behave just like normal variables.
	//! \param &v reference to a native variable of type T
	Scalar<T> &operator=(const T &v);
	//! assignment operator from a Scalar<T> object
	template <typename U> Scalar<T> &operator=(const Scalar<U> &v);
	Scalar<T> &operator=(const Scalar<T> &v);

	//what cannot be done with the assignement operator:
	//an object of type Scalar is assigned to an object of type T
	//this is done here with the conversion operator!
	//! conversion operator
	operator T() {
		return _value;
	}

	//! return the value of a Scalar object
	T& getValue() {
		return _value;
	}

	//! return the value of a Scalar object
	T getValue() const {
		return _value;
	}

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



	//clearly - the ostream operator must be overloaded
	//! stream operator for console output
	friend std::ostream &operator<<<> (std::ostream &, const Scalar<T> &);

	//for each of the arithmetic operators three cases must be
	//taken into account:
	//1.) Scalar .Op. T
	//2.) T .Op. Scalar
	//3.) Scalar .Op. Scalar
	//in all cases the result will be of type Scalar.
	//this is no problem even if the result will be assigned to an
	//object of type T (in this case the conversion operator
	//does the job).
	//! operator + for Scalar<T> + Scalar<T>
	friend Scalar<T> operator+<> (const Scalar<T> &a, const Scalar<T> &b);
	//! operator + for T + Scalar<T>
	friend Scalar<T> operator+<> (const T& a, const Scalar<T> &b);
	//! operator + for Scalar<T> + T
	friend Scalar<T> operator+<> (const Scalar<T> &a, const T&b);

	//! operator - for Scalar<T> - Scalar<T>
	friend Scalar<T> operator-<> (const Scalar<T> &a, const Scalar<T> &b);
	//! operator - for T - Scalar<T>
	friend Scalar<T> operator-<> (const T& a, const Scalar<T> &b);
	//! operator - for Scalar<T> - T
	friend Scalar<T> operator-<> (const Scalar<T> &a, const T &b);

	//! operator * for Scalar<T> * Scalar<T>
	friend Scalar<T> operator*<> (const Scalar<T> &a, const Scalar<T> &b);
	//! operator * for T * Scalar<T>
	friend Scalar<T> operator*<> (const T& a, const Scalar<T> &b);
	//! operator * for Scalar<T>*T
	friend Scalar<T> operator*<> (const Scalar<T> &a, const T& b);

	//! operator / for Scalar<T> / Scalar<T>
	friend Scalar<T> operator/<> (const Scalar<T> &a, const Scalar<T> &b);
	//! operator / for T / Scalar<T>
	friend Scalar<T> operator/<> (const T& a, const Scalar<T> &b);
	//! operator / for Scalar<T>/T
	friend Scalar<T> operator/<> (const Scalar<T> &a, const T &b);

	//! comparison operator == for Scalar<T> == Scalar<T>
	friend bool operator==<> (const Scalar<T> &a, const Scalar<T> &b);
	//! comparison operator == for Scalar<T>==T
	friend bool operator==<> (const Scalar<T> &a, const T &b);
	//! comparison operator == for T == Scalar<T>
	friend bool operator==<> (const T &a, const Scalar<T> &b);

	//overload combind arithmetics and assignment operators
	//! unary and inplace / operator for Scalar<T> /= T
	Scalar<T> &operator/=(const T &);
	//! unary and inplace / operator for Scalar<T> /= Scalar<T>
	Scalar<T> &operator/=(const Scalar<T> &v);
	//! unary and inplace + operator for Scalar<T> += T
	Scalar<T> &operator+=(const T &v);
	//! unary and inplace + operator for Scalar<T> += Scalar<T>
	Scalar<T> &operator+=(const Scalar<T> &v);
	//! unary and inplace - operator for Scalar<T> -= T
	Scalar<T> &operator-=(const T &v);
	//! unary and inplace - operator for Scalar<T> -= Scalar<T>
	Scalar<T> &operator-=(const Scalar<T> &v);
	//! unary and inplace * operator for Scalar<T> *= T
	Scalar<T> &operator*=(const T &v);
	//! unary and inplace * operator for Scalar<T> *= Scalar<T>
	Scalar<T> &operator*=(const Scalar<T> &v);

	//! get a void pointer to the data
	virtual void *getVoidPtr(){
		return (void *)(&_value);
	}

	virtual PNITypeID getTypeID() const{
		return PNITypeInfo<T>::TypeID;
	}

};

//==================private check methods==================================================
template<typename T>
template<typename U> void Scalar<T>::_type_is_compatible(const U &v) const{
	EXCEPTION_SETUP("template<typename T> template<typename U> bool Scalar<T>::_type_is_compatible()");

	//one cannot assign a complex number to a non-complex float number
	if((!TypeInfo<T>::isComplex())&&(TypeInfo<U>::isComplex())){
		EXCEPTION_INIT(TypeError,"Cannot convert a complex scalar to a non complex type!");
		EXCEPTION_THROW();
	}

	//one cannot assign securely assign a float number to an integer
	if((TypeInfo<T>::isInteger())&&(!TypeInfo<U>::isInteger())){
		EXCEPTION_INIT(TypeError,"Cannot convert a float value to an integer!");
		EXCEPTION_THROW();
	}

	//in general we can assign values only to numbers
	if(TypeInfo<T>::getSize() < TypeInfo<U>::getSize()){
		EXCEPTION_INIT(SizeMissmatchError,"Cannot convert scalar to a smalle type!");
		EXCEPTION_THROW();
	}

	//if we made it until here we have to check for sign
	if((!TypeInfo<T>::isSigned())&&(TypeInfo<T>::isSigned())){
		//we have to check the size of the
		if(v<0){
			EXCEPTION_INIT(RangeError,"Cannot assign a negative number to an unsigned type!");
			EXCEPTION_THROW();
		}
	}
}

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
template<typename T> template<typename U> void Scalar<T>::setValue(const U &v){
	_value = (T)v;

}

template<typename T> template<typename U> void Scalar<T>::setValue(const Scalar<U> &s){
	U v = s._value();

	setValue(v);
}

//======================unary arithmetic operators=========================================
template<typename T> Scalar<T>& Scalar<T>::operator/=(const T &v) {
	*this = *this / v;
	return *this;
}

template<typename T> Scalar<T>& Scalar<T>::operator/=(const Scalar<T> &v) {
	*this = *this / v;
	return *this;
}

template<typename T> Scalar<T>& Scalar<T>::operator+=(const T &v) {
	*this = *this + v;
	return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator+=(const Scalar<T> &v) {
	*this = *this + v;
	return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator-=(const T &v) {
	*this = *this - v;
	return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator-=(const Scalar<T> &v) {
	*this = *this - v;
	return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator*=(const T &v) {
	*this = *this * v;
	return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator*=(const Scalar<T> &v) {
	*this = *this * v;
	return *this;
}

//=======================comparison operator=================================
template<typename T> bool operator==(const Scalar<T> &a, const Scalar<T> &b) {
	return (a._value == b._value);
}

template<typename T> bool operator==(const T& a, const Scalar<T> &b) {
	return (a == b._value);
}

template<typename T> bool operator==(const Scalar<T> &a, const T& b) {
	return (a._value == b);
}

//overloaded output operator
template<typename T> std::ostream &operator<<(std::ostream &o,
		const Scalar<T> &v) {
	o << v._name << " = " << v._value << " " << v._unit << " (" << v._description
			<< ")";

	return o;
}

//overloaded assignment operators - these operators must be class members
template<typename T> Scalar<T> &Scalar<T>::operator=(const T &v) {
	_value = v;
	return *this;
}

template<typename T>
template<typename U> Scalar<T> &Scalar<T>::operator=(const Scalar<U> &v){
	EXCEPTION_SETUP("template<typename T> template<typename U> Scalar<T> &"
					 "Scalar<T>::operator=(const Scalar<U> &v)");
	//check if assignment is possible

	if((void *)this != (void *)(&v)){
		try{
			_type_is_compatible(v.getValue());
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
	std::cout<<"native assignment"<<std::endl;
	if(this != &s){
		(*this).setValue(s.getValue());
		(*this).setName(s.getName());
		(*this).setUnit(s.getUnit());
		(*this).setDescription(s.getDescription());
	}
	return *this;
}

//overloaded addition operators
template<typename T> Scalar<T> operator+(const Scalar<T> &a, const Scalar<T> &b) {
	Scalar<T> tmp = b; //we use here the copy constructor to create
	//a new object of type Scalar<T>

	tmp._value = a._value + b._value;

	return tmp;
}

template<typename T> Scalar<T> operator+(const T& a, const Scalar<T> &b) {
	Scalar<T> tmp = b;

	tmp._value = a + b._value;

	return tmp;
}

template<typename T> Scalar<T> operator+(const Scalar<T> &a, const T&b) {
	Scalar<T> tmp = a;
	tmp = a._value + b;
	return tmp;
}

//overloaded subtraction operator
template<typename T> Scalar<T> operator-(const Scalar<T> &a, const Scalar<T> &b) {
	Scalar<T> tmp = b;

	tmp._value = a._value - b._value;

	return tmp;
}

template<typename T> Scalar<T> operator-(const T& a, const Scalar<T> &b) {
	Scalar<T> tmp = b;
	tmp._value = a - b._value;
	return tmp;
}

template<typename T> Scalar<T> operator-(const Scalar<T> &a, const T &b) {
	Scalar<T> tmp = b;
	tmp._value = a._value - b;
	return tmp;
}

//overloading the multiplication operator
template<typename T> Scalar<T> operator*(const Scalar<T> &a, const Scalar<T> &b) {
	Scalar<T> tmp = b;
	tmp._value = a._value * b._value;
	return tmp;
}

template<typename T> Scalar<T> operator*(const T& a, const Scalar<T> &b) {
	Scalar<T> tmp = b;
	tmp._value = a * b._value;
	return tmp;
}

template<typename T> Scalar<T> operator*(const Scalar<T> &a, const T& b) {
	Scalar<T> tmp = b;
	tmp._value = a._value * b;
	return tmp;
}

//overloading the division operator
template<typename T> Scalar<T> operator/(const Scalar<T> &a, const Scalar<T> &b) {
	Scalar<T> tmp = b;
	tmp._value = a._value / b._value;
	return tmp;
}

template<typename T> Scalar<T> operator/(const T& a, const Scalar<T> &b) {
	Scalar<T> tmp = b;
	tmp._value = a / b._value;
	return tmp;
}

template<typename T> Scalar<T> operator/(const Scalar<T> &a, const T &b) {
	Scalar<T> tmp = a;
	tmp._value = a._value / b;
	return tmp;
}

//declare some useful default types
typedef Scalar<char> Int8Scalar;
typedef Scalar<unsigned char> UInt8Scalar;
typedef Scalar<short> Int16Scalar;
typedef Scalar<unsigned short> UInt16Scalar;
typedef Scalar<int> Int32Scalar;
typedef Scalar<unsigned int> UInt32Scalar;
typedef Scalar<long> Int64Scalar;
typedef Scalar<unsigned long> UInt64Scalar;

typedef Scalar<float> Float32Scalar;
typedef Scalar<double> Float64Scalar;
typedef Scalar<long double> Float128Scalar;

typedef Scalar<std::complex<float> > Complex32Scalar;
typedef Scalar<std::complex<double> > Complex64Scalar;
typedef Scalar<std::complex<long double> > Complex128Scalar;

//end of namespace
}
}

#endif /* SCALAR_HPP_ */
