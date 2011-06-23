/*
 * TIFFRational.hpp
 *
 *  Created on: Jun 17, 2011
 *      Author: eugen
 */

#ifndef TIFFRATIONAL_HPP_
#define TIFFRATIONAL_HPP_

#include <iostream>

#include "../PNITypes.hpp"

namespace pni{
namespace utils{


template<typename T> class Rational;
template<typename T> std::ostream &operator<<(std::ostream &o,const Rational<T> &r);

//! \ingroup IO
//! \brief rational type for TIFF IFD entries

//! IFD entries in TIFF files can consist of a rational number. This class
//! implements such a type as a template.
template<typename T> class Rational{
protected:
	T _numerator;    //!< numerator of the rational number
	T _denominator;  //!< denominator of the rational number
public:
	//! default constructor
	Rational();
	//! copy constructor
	Rational(const Rational &o);
	//! standard constructor
	Rational(const T &,const T&);
	//! destructor
	virtual ~Rational(){}

	//! set the numerator
	virtual void setNumerator(const T &);
	//! get the numerator
	virtual T getNumerator() const;

	//! assignment operator
	virtual Rational<T> &operator=(const Rational<T> &r);

	//! set the denominator
	virtual void setDenominator(const T &);
	//! get the denominator
	virtual T getDenominator() const;

	//! operator for console output
	friend std::ostream &operator<<<> (std::ostream &o,const Rational<T> &r);

};

template<typename T> Rational<T>::Rational(){
	_numerator = 0;
	_denominator = 0;
}

template<typename T> Rational<T>::Rational(const Rational<T> &r){
	_numerator = r._numerator;
	_denominator = r._denominator;
}

template<typename T> Rational<T>::Rational(const T &n,const T &d){
	_numerator = n;
	_denominator = d;
}

template<typename T> void Rational<T>::setNumerator(const T &n){
	_numerator = n;
}

template<typename T> T Rational<T>::getNumerator() const {
	return _numerator;
}

template<typename T> void Rational<T>::setDenominator(const T &d){
	_denominator = d;
}

template<typename T> T Rational<T>::getDenominator() const {
	return _denominator;
}

template<typename T> Rational<T> &Rational<T>::operator=(const Rational<T> &r){
	if(this != &r){
		_numerator = r._numerator;
		_denominator = r._denominator;
	}
	return *this;
}

template<typename T> std::ostream &operator<<(std::ostream &o,const Rational<T> &r){
	o<<r._numerator<<"/"<<r._denominator;
	return o;
}

typedef Rational<UInt32> URational;
typedef Rational<Int32> SRational;

//end namespaces
}
}


#endif /* TIFFRATIONAL_HPP_ */
