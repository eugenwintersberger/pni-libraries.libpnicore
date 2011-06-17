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

template<typename T> class Rational{
protected:
	T _numerator;
	T _denominator;
public:
	Rational();
	Rational(const Rational &o);
	Rational(const T &,const T&);
	virtual ~Rational(){}

	virtual void setNumerator(const T &);
	virtual T getNumerator() const;

	virtual Rational<T> &operator=(const Rational<T> &r);

	virtual void setDenominator(const T &);
	virtual T getDenominator() const;

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
