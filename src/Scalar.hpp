/*
 * Scalar.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: eugen
 */

#ifndef SCALAR_HPP_
#define SCALAR_HPP_

#include <complex>

#include "ScalarObject.hpp"

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

template<typename T> class Scalar: public ScalarObject {
protected:
	T _value;
public:
	//default constructor
	Scalar();
	//copy constructor
	Scalar(const Scalar<T> &);
	//setting value  bue use default constructor for the
	//base class
	Scalar(const T &v);
	Scalar(const T &v, const String &n, const String &u);
	Scalar(const T &v, const char *n, const char *u);
	Scalar(const T &v, const String &n, const String &d, const String &u);
	Scalar(const T &v, const char *n, const char *d, const char *u);
	Scalar(const String &n, const String &u);
	Scalar(const char *n, const char *u);
	Scalar(const String &n, const String &d, const String &u);
	Scalar(const char *n, const char *d, const char *u);
	//destructor
	virtual ~Scalar();

	//for the assignment operator two cases must be considered
	//1.) An object of type Scalar is assigned to a Scalar instance
	//2.) An object of type T is assigned to a Scalar instance
	//basically the assignment operator handles cases where the Scalar object
	//is an l-value of an expression.
	//What is still missing here is the case that the r-value of the
	//expression is of different type than T. This case still requires
	//handling to avoid problems later on.
	Scalar<T> &operator=(const T &v);
	Scalar<T> &operator=(const Scalar<T> &v);

	//this is some canonical operation that should be
	//implemented nearly everywhere
	const T& getValue() {
		return _value;
	}

	//what cannot be done with the assignement operator:
	//an object of type Scalar is assigned to an object of type T
	//this is done here with the conversion operator!
	operator T() {
		return _value;
	}

	//clearly - the ostream operator must be overloaded
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
	friend Scalar<T> operator+<> (const Scalar<T> &a, const Scalar<T> &b);
	friend Scalar<T> operator+<> (const T& a, const Scalar<T> &b);
	friend Scalar<T> operator+<> (const Scalar<T> &a, const T&b);

	friend Scalar<T> operator-<> (const Scalar<T> &a, const Scalar<T> &b);
	friend Scalar<T> operator-<> (const T& a, const Scalar<T> &b);
	friend Scalar<T> operator-<> (const Scalar<T> &a, const T &b);

	friend Scalar<T> operator*<> (const Scalar<T> &a, const Scalar<T> &b);
	friend Scalar<T> operator*<> (const T& a, const Scalar<T> &b);
	friend Scalar<T> operator*<> (const Scalar<T> &a, const T& b);

	friend Scalar<T> operator/<> (const Scalar<T> &a, const Scalar<T> &b);
	friend Scalar<T> operator/<> (const T& a, const Scalar<T> &b);
	friend Scalar<T> operator/<> (const Scalar<T> &a, const T &b);

	friend bool operator==<> (const Scalar<T> &a, const Scalar<T> &b);
	friend bool operator==<> (const Scalar<T> &a, const T &b);
	friend bool operator==<> (const T &a, const Scalar<T> &b);

	//overload combind arithmetics and assignment operators
	Scalar<T> &operator/=(const T &);
	Scalar<T> &operator/=(const Scalar<T> &v);
	Scalar<T> &operator+=(const T &v);
	Scalar<T> &operator+=(const Scalar<T> &v);
	Scalar<T> &operator-=(const T &v);
	Scalar<T> &operator-=(const Scalar<T> &v);
	Scalar<T> &operator*=(const T &v);
	Scalar<T> &operator*=(const Scalar<T> &v);

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

template<typename T> Scalar<T>::Scalar(const T &v, const char *n, const char *u) :
	ScalarObject(n, u) {
	_value = v;
}

template<typename T> Scalar<T>::Scalar(const T &v, const String &n,
		const String &d, const String &u) :
	ScalarObject(n, d, u) {
	_value = v;
}

template<typename T> Scalar<T>::Scalar(const T &v, const char *n,
		const char *d, const char *u) :
	ScalarObject(n, d, u) {
	_value = v;
}

template<typename T> Scalar<T>::Scalar(const String &n, const String &u) :
	ScalarObject(n, u) {
	_value = 0;
}

template<typename T> Scalar<T>::Scalar(const char *n, const char *u) :
	ScalarObject(n, u) {
	_value = 0;
}

template<typename T> Scalar<T>::Scalar(const String &n, const String &d,
		const String &u) :
	ScalarObject(n, d, u) {
	_value = 0;
}

template<typename T> Scalar<T>::Scalar(const char *n, const char *d,
		const char *u) :
	ScalarObject(n, d, u) {
	_value = 0;
}

template<typename T> Scalar<T>::~Scalar() {
	_value = 0;
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

template<typename T> Scalar<T> &Scalar<T>::operator=(const Scalar<T> &v) {
	if (this != &v) {
		_value = v._value;
		_name = v._name;
		_unit = v._unit;
		_description = v._description;
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
