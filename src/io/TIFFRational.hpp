/*
 * Implementation of class TIFFRational
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
 * Declaration of class TIFFRational.
 *
 * Created on: Jun 17, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef TIFFRATIONAL_HPP_
#define TIFFRATIONAL_HPP_

#include <iostream>

#include "../Types.hpp"

namespace pni{
namespace utils{


template<typename T> class Rational;
template<typename T> std::ostream &operator<<(std::ostream &o,const Rational<T> &r);

//! \ingroup io_classes
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
