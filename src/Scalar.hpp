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

namespace pni{
namespace utils{

//this is the first part to make the friend declaration for templates for
//correctly - this code is just to imform the compiler!
template<typename T> class Scalar;
template<typename T> std::ostream &operator<<(std::ostream &o,const Scalar<T> &v);

template<typename T> Scalar<T> operator+(const Scalar<T> &a,const Scalar<T> &b);
template<typename T> Scalar<T> operator+(const T& a,const Scalar<T> &b);
template<typename T> Scalar<T> operator+(const Scalar<T> &a,const T&b);

template<typename T> Scalar<T> operator-(const Scalar<T> &a,const Scalar<T> &b);
template<typename T> Scalar<T> operator-(const T& a,const Scalar<T> &b);
template<typename T> Scalar<T> operator-(const Scalar<T> &a,const T &b);

template<typename T> Scalar<T> operator*(const Scalar<T> &a,const Scalar<T> &b);
template<typename T> Scalar<T> operator*(const T& a,const Scalar<T> &b);
template<typename T> Scalar<T> operator*(const Scalar<T> &a,const T& b);

template<typename T> Scalar<T> operator/(const Scalar<T> &a,const Scalar<T> &b);
template<typename T> Scalar<T> operator/(const T& a,const Scalar<T> &b);
template<typename T> Scalar<T> operator/(const Scalar<T> &a,const T &b);

template<typename T> bool operator==(const Scalar<T> &a,const Scalar<T> &b);
template<typename T> bool operator==(const T& a,const Scalar<T> &b);
template<typename T> bool operator==(const Scalar<T> &a,const T& b);



template<typename T>class Scalar:public ScalarObject{
    protected:
        T value;
    public:
        //default constructor
        Scalar():ScalarObject(){}
        //copy constructor
        Scalar(const Scalar<T> &);
        //setting value  bue use default constructor for the
        //base class
        Scalar(const T &v):ScalarObject(){value = v;}
        //destructor
        virtual ~Scalar(){}

        //for the assignement operator two cases must be considered
        //1.) An object of type Scalar is assigned to a Scalar instance
        //2.) An object of type T is assigned to a Scalar instance
        Scalar<T> &operator=(const T &v);
        Scalar<T> &operator=(const Scalar<T> &v);

        //this is some cannonical operation that should be
        //implemented nearly everywhere
        const T& getValue() { return value;}

        //what cannot be done with the assignement operator:
        //an object of type Scalar is assigned to an object of type T
        //this is done here with the conversion operator!
        operator T() {return value;}

        //clearly - the ostream operator must be overloaded
        friend std::ostream &operator<< <> (std::ostream &,const Scalar<T> &);


        //for each of the arithmetic operators three cases must be
        //taken into account:
        //1.) Scalar .Op. T
        //2.) T .Op. Scalar
        //3.) Scalar .Op. Scalar
        //in all cases the result will be of type Scalar.
        //this is no problem even if the result will be assigned to an
        //object of type T (in this case the conversion operator
        //does the job).
        friend Scalar<T> operator+ <> (const Scalar<T> &a,const Scalar<T> &b);
        friend Scalar<T> operator+ <> (const T& a,const Scalar<T> &b);
        friend Scalar<T> operator+ <> (const Scalar<T> &a,const T&b);

        friend Scalar<T> operator- <> (const Scalar<T> &a,const Scalar<T> &b);
        friend Scalar<T> operator- <> (const T& a,const Scalar<T> &b);
        friend Scalar<T> operator- <> (const Scalar<T> &a,const T &b);

        friend Scalar<T> operator* <> (const Scalar<T> &a,const Scalar<T> &b);
        friend Scalar<T> operator* <> (const T& a,const Scalar<T> &b);
        friend Scalar<T> operator* <> (const Scalar<T> &a,const T& b);

        friend Scalar<T> operator/ <> (const Scalar<T> &a,const Scalar<T> &b);
        friend Scalar<T> operator/ <> (const T& a,const Scalar<T> &b);
        friend Scalar<T> operator/ <> (const Scalar<T> &a,const T &b);

        friend bool operator== <> (const Scalar<T> &a,const Scalar<T> &b);
        friend bool operator== <> (const Scalar<T> &a,const T &b);
        friend bool operator== <> (const T &a,const Scalar<T> &b);

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

template<typename T> Scalar<T>& Scalar<T>::operator/=(const T &v){
    *this = *this / v;
    return *this;
}

template<typename T> Scalar<T>& Scalar<T>::operator/=(const Scalar<T> &v){
    *this = *this / v;
    return *this;
}

template<typename T> Scalar<T>& Scalar<T>::operator+=(const T &v){
    *this = *this+v;
    return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator+=(const Scalar<T> &v){
    *this = *this+v;
    return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator-=(const T &v){
    *this = *this - v;
    return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator-=(const Scalar<T> &v){
    *this = *this - v;
    return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator*=(const T &v){
    *this = *this * v;
    return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator*=(const Scalar<T> &v){
    *this = *this * v;
    return *this;
}



template<typename T> bool operator==(const Scalar<T> &a,const Scalar<T> &b){
    return (a.value == b.value);
}

template<typename T> bool operator==(const T& a,const Scalar<T> &b){
    return (a == b.value);
}

template<typename T> bool operator==(const Scalar<T> &a,const T& b){
    return (a.value == b);
}

template<typename T> Scalar<T>::Scalar(const Scalar<T> &s){
    value = s.value;
    _unit = s._unit;
    _description = s._description;
    _name = s._name;
}


template<typename T> Scalar<T>::Scalar(const T &v,const String &n):DataValue(n){
    value = v;
}

template<typename T> Scalar<T>::Scalar(const T &v,const String &n,const String &u):DataValue(n,u){
    value = v;
}

template<typename T> Scalar<T>::Scalar(const T &v,const String &n,const String &u,const String &d):
                                DataValue(n,u,d)
{
    value = v;
}



//overloaded output operator
template<typename T> std::ostream &operator<<(std::ostream &o,const Scalar<T> &v){
    o<<v.name<<" = "<<v.value<<" "<<v.unit<<" ("<<v.description<<")";

    return o;
}

//overloaded assignment operators - these operators must be class members
template<typename T> Scalar<T> &Scalar<T>::operator=(const T &v){
    value = v;
    return *this;
}

template<typename T> Scalar<T> &Scalar<T>::operator=(const Scalar<T> &v){
    if(this != &v){
        value = v.value;
        _name = v._name;
        _unit = v._unit;
        _description = v._description;
    }
    return *this;
}


//overloaded addition operators
template<typename T> Scalar<T> operator+ (const Scalar<T> &a,const Scalar<T> &b){
    Scalar<T> tmp = b;  //we use here the copy constructor to create
                        //a new object of type Scalar<T>

    tmp.value = a.value + b.value;

    return tmp;
}

template<typename T> Scalar<T> operator+(const T& a,const Scalar<T> &b){
    Scalar<T> tmp = b;

    tmp.value = a+b.value;

    return tmp;
}

template<typename T> Scalar<T> operator+(const Scalar<T> &a,const T&b){
    Scalar<T> tmp = a;
    tmp = a.value + b;
    return tmp;
}

//overloaded subtraction operator
template<typename T> Scalar<T> operator-(const Scalar<T> &a,const Scalar<T> &b){
    Scalar<T> tmp = b;

    tmp.value = a.value - b.value;

    return tmp;
}

template<typename T> Scalar<T> operator-(const T& a,const Scalar<T> &b){
    Scalar<T> tmp = b;
    tmp.value = a-b.value;
    return tmp;
}

template<typename T> Scalar<T> operator-(const Scalar<T> &a,const T &b){
    Scalar<T> tmp = b;
    tmp.value = a.value - b;
    return tmp;
}

//overloading the multiplication operator
template<typename T> Scalar<T> operator*(const Scalar<T> &a,const Scalar<T> &b){
    Scalar<T> tmp = b;
    tmp.value = a.value*b.value;
    return tmp;
}

template<typename T> Scalar<T> operator*(const T& a,const Scalar<T> &b){
    Scalar<T> tmp = b;
    tmp.value = a*b.value;
    return tmp;
}

template<typename T> Scalar<T> operator*(const Scalar<T> &a,const T& b){
    Scalar<T> tmp = b;
    tmp.value = a.value*b;
    return tmp;
}

//overloading the division operator
template<typename T> Scalar<T> operator/(const Scalar<T> &a,const Scalar<T> &b){
    Scalar<T> tmp = b;
    tmp.value = a.value/b.value;
    return tmp;
}

template<typename T> Scalar<T> operator/(const T& a,const Scalar<T> &b){
    Scalar<T> tmp = b;
    tmp.value = a/b.value;
    return tmp;
}

template<typename T> Scalar<T> operator/(const Scalar<T> &a,const T &b){
    Scalar<T> tmp = a;
    tmp.value = a.value/b;
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
