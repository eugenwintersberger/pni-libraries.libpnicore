/*
 * Declaration of class template Scalar<T>
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
 * Scalar<T> represents a scalar numeric value of a particular type along
 * with basic arithmetic operations.
 *
 * Created on: Jun 9, 2011
 *     Author: Eugen Wintersberger
 *
 */


#ifndef SCALAR_HPP_
#define SCALAR_HPP_

#include <iostream>
#include <complex>
#include <limits>

#include "Types.hpp"
#include "NumericObject.hpp"
#include "TypeInfo.hpp"
#include "Exceptions.hpp"
#include "ResultTypeTrait.hpp"
#include "TypeIDMap.hpp"
#include "ComplexUtils.hpp"
#include "type_conversion.hpp"
#include "CompType.hpp"

namespace pni {
namespace utils {

using namespace boost::numeric;

    /*! \ingroup data_classes
    \brief Scalar template for scalar values

    Basically one can consider this as a concrete implementation of
    the class ScalarObject. Along with all other attributes of a NumericObject
    this template holds a single datum of an numeric type.
    To make such a template useful it must not only provide support copy and
    assignment operations, in addition full support for basic arithmetic operations
    must be available.
    
    In connection with the Scalar object the assignment and conversion operator
    need some special care.
    The assignment operator comes in several flavors. Basically two cases
    of assignment involving a Scalar<T> object must be considered
    - an object of type Scalar<T> is assigned to an other object of type Scalar<U> where
      U is either the same as T or a different numeric type
    - an object of type T is assigned to an object of type Scalar<U> where U is the same
      or a different type than T
    
    Thus, the assignment operator handles all cases where the Scalar object is
    the l-value of an expression. Templates are used for cases where the r-value
    of such an assignment expression is of different type. If the types do not
    match exceptions are raised. In cases where two objects of type Scalar<T> are
    assigned to each other not only the value but also the name, description, and
    unit of the r-value object are transfered to the l-value object.
    
    An other situation is that the l-value of an expression is a simple variable
    of native type T and the r-value an object of type Scalar<T>. This is
    managed by the conversion operator. In cases where the type of the r-value and
    the l-value differ there should be no problem as long as there is an implicit
    conversion between the two types.
    
    A critical aspect of the Scalar<T> template are the arithmetic operations. All basic
    operations (+,*,-,/) are supported. The unary version of these operations with an
    object of Scalar<T> as an l-value are implemented as class members where the binary
    versions are simple template functions. While for the former ones the type of the
    result of the operation can be simply derived from the instance of the Scalar<T> object
    The situation is not that easy for the binary function templates. These function
    templates use fixed type selections where the result type is derived from the
    argument types. This should avoid overflows during computation. The fact that a temporary
    object of an appropriate type is created avoids us to implement complex tests to
    determine whether or not an operation is allowed. However, in the end the result
    is assigned to an object of a particular type. Thus, the temporary type and the
    target type must be assignable - otherwise an exception will be thrown.
    It is clear that for the binary versions of the arithmetic operators temporary objects
    are created and returned by value. However, since the scalar objects are pretty small
    this effort should not matter too much.
    */
    template<typename T> class Scalar:public NumericObject
    {
        private:
            T _value; //!< object holding the value of the Scalar object
        public:
            //================public data types================================
            typedef std::shared_ptr<Scalar<T> > shared_ptr; //!< shared pointer type
            typedef std::unique_ptr<Scalar<T> > unique_ptr; //!< unique pointer type
            typedef T value_type; //!< type of the scalar object
            
            //===============public members====================================
            //! type ID of the data type held by the scalar
            static const TypeID type_id = TypeIDMap<T>::type_id;
            //! memory size of the element type
            static const size_t value_size = sizeof(T);

            //====================constructors and destructor==================
            //! default constructor
            Scalar():NumericObject(),_value(0)
            {}
            
            //-----------------------------------------------------------------
            //! copy constructor
            Scalar(const Scalar<T> &s):NumericObject(s),_value(s._value)
            {}

            //-----------------------------------------------------------------
            //! move constructor
            Scalar(Scalar<T> &&s):
                NumericObject(std::move(s)),
                _value(std::move(s._value))
            {}

            //-----------------------------------------------------------------
            /*! \brief copy conversion constructor

            Constructs Scalar<T> from a scalar of a different type. 
            \throws TypeError if conversion fails
            */
            template<typename U> Scalar(const Scalar<U> &o):
                NumericObject(o),
	            _value(convert_type<T>(o.value()))
            {}
                
            //-----------------------------------------------------------------
            /*! constructor using T value

            Constructs Scalar instance from a single value of type T.
            \param v value of type T
            */
            Scalar(const T &v):NumericObject(),_value(v)
            {}

            //-----------------------------------------------------------------
            /*! \brief constructor

            Constructor setting the value, name, and physical unit of the 
            Scalar object.
            \param v value of type T
            \param n name of the object as String
            \param u unit of the object as String
            */
            Scalar(const T &v, const String &n, const String &u):
                NumericObject(n,u),
                _value(v)
            {}

            //-----------------------------------------------------------------
            /*! \brief constructor

            Constructor setting the value, name, description, and physical 
            unit of the Scalar object.
            \param v value of type T
            \param n name of the object as String
            \param u unit of the object as String
            \param d description of the object as String
            */
            Scalar(const T &v, const String &n, const String &u, 
                   const String &d):
                NumericObject(n,u,d),
                _value(v)
            {}

            //-----------------------------------------------------------------
            /*! \brief constructor

            Constructor setting name and unit of the Scalar object.
            \param n name of the object as String
            \param u physical unit of the object as String
            */
            Scalar(const String &n, const String &u):
                NumericObject(n,u),
                _value(0)
            {}

            //-----------------------------------------------------------------
            /*! \brief constructor

            Constructor setting name, description, and unit of the Scalar object.
            \param n name of the object as String
            \param u physical unit of the object as String
            \param d description of the object as String
            */
            Scalar(const String &n, const String &u, const String &d):
                NumericObject(n,u,d),
                _value(0)
            {}

            //-----------------------------------------------------------------
            //! destructor
            ~Scalar() {}


            //=================assignment operators============================
            /*! \brief assignment from T value

            Assigns a value of type T to the scalar.
            \param v value to assign
            */
            Scalar<T> &operator=(const T &v)
            {
                this->_value = v;
                return *this;
            }

            //-----------------------------------------------------------------
            /*! \brief assignment from U value

            Assignment from a different type U. Throws an exception if
            conversion from U to T fails.
            \param v value of type U
            */
            template<typename U> Scalar<T> &operator=(const U &v)
            {
                this->_value = convert_type<T>(v);
                return *this;
            }

            //-----------------------------------------------------------------
            /*! \brief assignment from Scalar<T>

            This is the most trivial case. An object of type Scalar<T> is 
            assigned to an other object of type Scalar<T>.
            \param v value of Scalar<T> to assign
            */
            Scalar<T> &operator=(const Scalar<T> &v)
            {
                if(this == &v) return *this;
                NumericObject::operator=(v);
                this->_value = v._value;
                return *this;
            }

            //------------------------------------------------------------------
            /*! assignment operator from a Scalar<U> to Scalar<T>

            The most complex situation of assignment - an object of Scalar<U> is
            assigned to an object of Scalar<T> where U and T are different types.
            The template method performs type checking in order to figure out
            if the types are compatible or not at runtime and raises an exception
            if this is not the case.
            \throws TypeError thrown if U cannot be assigned to T
            \param v reference to an object of type Scalar<U>
            */
            template <typename U> Scalar<T> &operator=(const Scalar<U> &v)
            {
                NumericObject::operator=(v);
                this->_value = convert_type<T>(v.value());
                return *this;
            }

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
            template<typename U> operator U() const 
            {
                return convert_type<U>(_value);
            }



            //! return the value of a Scalar object

            //! Returns the value stored in the scalar Object. Since the value is returns
            //! this method cannot be used to alter the content of a Scalar object.
            //! Since we can use the conversion operator for the same purpose this
            //! method was implemented just for convenience and might be useful if a
            //! pointer to a scalar object is used.
            //! \return value of the Scalar object
            T value() const 
            {
                return _value;
            }

            //! set value from scalar object

            //! Sets the value of the object from an other object of type Scalar<T>.
            //! No type checking is needed in this case because the objects are of same type.
            //! Unlike the assignment operator only the value of the two Scalar<T> objects
            //! are equal afer a call to this method. All other attributes of the class
            //! remain the same.
            //! \param v reference to the object from which the value should be taken
            void value(const Scalar<T> &v) 
            { 
                this->_value = v._value; 
            }

            //! set value from variable

            //! Sets the value of the object from a variable of type T. Since the variable
            //! is of same data type than the template type of the scalar object no type
            //! checking is needed. This method does the same as the corresponding
            //! assignment operator.
            //! \see Scalar<T> &operator=(const T &v)
            //! \param v reference to a variable of type T
            void value(const T &v) 
            { 
                this->_value = v; 
            }

            //! template to set the value of a Scalar

            //! Template method to set the value of a Scalar object
            //! from a Scalar object of different type. This method is
            //! useful if only a pointer exists to a Scalar<T> object
            //! and therefore the = operator cannot be called in an easy manner.
            //! \param &v reference to a Scalar object of type U
            template<typename U> void value(const Scalar<U> &v)
            {
                this->_value = convert_type<T>(v.value());
            }
            //! template to set the value of a Scalar

            //! Template method to set the value of a Scalar object
            //! from a native variable of type U. This method is particularly
            //! useful if only a pointer to a Scalar<T> object exists
            //! and the = operator cannot be called in a simple manner.
            //! \param &v reference to a variable of type U
            template<typename U> void value(const U &v)
            {
                this->_value = convert_type<T>(v);
            }

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
            //! unary inplace / operator for Scalar<T> /= U
            template<typename U> Scalar<T> &operator/=(const U &v);
            //! unary and inplace / operator for Scalar<T> /= Scalar<T>
            Scalar<T> &operator/=(const Scalar<T> &v);
            //! unary and inplace / operator for 
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

            //-----------------------------------------------------------------
            /*! \brief get void pointer to data

            Returns a void pointer to the data held by the object.
            \return void pointer
            */
            void *void_ptr() { return (void *)(&_value); }

            //-----------------------------------------------------------------
            /*! \brief get const void pointer

            Return a const void pointer to the data held by the object.
            \return const void pointer
            */
            const void *void_ptr() const { return (const void *)(&_value); }

            //-----------------------------------------------------------------
            /*! \brief get pointer to data

            Return a pointer to the data held by the scalar
            \return pointer to data
            */
            T *ptr(){ return &_value; }

            //-----------------------------------------------------------------
            /*! \brief get const pointer to data

            Returns a const pointer to the data held by the scalar object.
            \return const pointer to data
            */
            const T *ptr() const { return (const T*)(&_value); }


    };


    //======================unary division operators============================
    template<typename T> Scalar<T>& Scalar<T>::operator/=(const T &v) 
    {
        typedef typename ResultTypeTrait<T,T>::DivResultType ResultType;

        ResultType a,b,res;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v);
        res = a/b;

        _value = convert_type<T>(res);

        return *this;
    }

    //--------------------------------------------------------------------------
    template<typename T>
    template<typename U> Scalar<T>& Scalar<T>::operator/=(const U &v) 
    {
        typedef typename ResultTypeTrait<T,U>::DivResultType ResultType;

        ResultType a,b,res;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v);
        res = a/b;

        _value = convert_type<T>(res);

        return *this;
    }

    //--------------------------------------------------------------------------
    template<typename T> Scalar<T>& Scalar<T>::operator/=(const Scalar<T> &v) 
    {
        typedef typename ResultTypeTrait<T,T>::DivResultType ResultType;

        ResultType a,b,res;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v.value());
        res = a/b;

        _value = convert_type<T>(res);

        return *this;
    }

    //-------------------------------------------------------------------------
    template<typename T>
    template<typename U> Scalar<T>& Scalar<T>::operator/=(const Scalar<U> &v)
    {
        typedef typename ResultTypeTrait<T,U>::DivResultType ResultType;

        ResultType a,b,res;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v.value());
        res = a/b;

        _value = convert_type<T>(res);
        return *this;
    }

    //===================unary addition operator================================
    template<typename T> Scalar<T>& Scalar<T>::operator+=(const T &v) 
    {
        typedef typename ResultTypeTrait<T,T>::AddResultType ResultType;
        ResultType res,a,b;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v);
        res = a+b;

        _value = convert_type<T>(res);

        return *this;
    }

    //--------------------------------------------------------------------------
    template<typename T>
    template<typename U> Scalar<T> &Scalar<T>::operator+=(const U &v)
    {
        typedef typename ResultTypeTrait<T,U>::AddResultType ResultType;
        ResultType res,a,b;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v);
        res = a+b;

        _value = convert_type<T>(res);

        return *this;
    }

    //--------------------------------------------------------------------------
    template<typename T> Scalar<T> &Scalar<T>::operator+=(const Scalar<T> &v) 
    {
        typedef typename ResultTypeTrait<T,T>::AddResultType ResultType;
        ResultType res,a,b;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v.value());
        res = a+b;

        _value = convert_type<T>(res);

        return *this;
    }

    //--------------------------------------------------------------------------
    template<typename T>
    template<typename U> Scalar<T> &Scalar<T>::operator+=(const Scalar<U> &v)
    {
        typedef typename ResultTypeTrait<T,U>::AddResultType ResultType;

        ResultType res,a,b;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v.value());
        res = a+b;

        _value = convert_type<T>(res);
        return *this;
    }

    //========================unary subtraction operator========================
    template<typename T> Scalar<T> &Scalar<T>::operator-=(const T &v) 
    {
        typedef typename ResultTypeTrait<T,T>::SubResulType ResultType;

        ResultType res,a,b;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v);
        res = a-b;
        _value = convert_type<T>(res);
        return *this;
    }

    //--------------------------------------------------------------------------
    template<typename T>
    template<typename U> Scalar<T> &Scalar<T>::operator-=(const U &v)
    {
        typedef typename ResultTypeTrait<T,U>::SubResultType ResultType;

        ResultType res,a,b;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v);
        res = a-b;

        _value = convert_type<T>(res);
        return *this;
    }

    //--------------------------------------------------------------------------
    template<typename T> Scalar<T> &Scalar<T>::operator-=(const Scalar<T> &v) 
    {
        typedef typename ResultTypeTrait<T,T>::SubResultType ResultType;

        ResultType res,a,b;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v.value());
        res = a-b;

        _value = convert_type<T>(res);

        return *this;
    }

    //--------------------------------------------------------------------------
    template<typename T>
    template<typename U> Scalar<T> &Scalar<T>::operator-=(const Scalar<U> &v)
    {
        typedef typename ResultTypeTrait<T,U>::SubResultType ResultType;

        ResultType result,a,b;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v.value());
        result = a - b;

        _value = convert_type<T>(result);
        return *this;
    }

    //====================Unary multiplication operator=========================
    template<typename T> Scalar<T> &Scalar<T>::operator*=(const T &v) 
    {
        typedef typename ResultTypeTrait<T,T>::MultResultType ResultType;

        ResultType result,a,b;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v);
        result = a*b;
        _value = convert_type<T>(result);

        return *this;
    }

    //--------------------------------------------------------------------------
    template<typename T>
    template<typename U> Scalar<T> &Scalar<T>::operator*=(const U &v)
    {
        typedef typename ResultTypeTrait<T,U>::MultResultType ResultType;

        ResultType result,a,b;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v);
        result = a * b;
        _value = convert_type<T>(result);

        return *this;
    }

    //--------------------------------------------------------------------------
    template<typename T> Scalar<T> &Scalar<T>::operator*=(const Scalar<T> &v) 
    {
        typedef typename ResultTypeTrait<T,T>::MultResultType ResultType;

        ResultType result,a,b;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v.value());
        result = a*b;
        _value = convert_type<T>(result);

        return *this;
    }

    //--------------------------------------------------------------------------
    template<typename T>
    template<typename U> Scalar<T> &Scalar<T>::operator*=(const Scalar<U> &v)
    {
        typedef typename ResultTypeTrait<T,U>::MultResultType ResultType;

        ResultType result,a,b;
        a = convert_type<ResultType>(_value);
        b = convert_type<ResultType>(v.value());
        result = a*b;

        _value = convert_type<T>(result);
        return *this;
    }

    //=======================comparison operator================================
    template<typename T> 
        bool operator==(const Scalar<T> &a, const Scalar<T> &b) 
    {
        return (a.value() == b.value());
    }

    //--------------------------------------------------------------------------
    template<typename T> 
        bool operator==(const T& a, const Scalar<T> &b) 
    {
        return (a == b.value());
    }

    //--------------------------------------------------------------------------
    template<typename T> 
        bool operator==(const Scalar<T> &a, const T& b) 
    {
        return (b==a);
    }

    //--------------------------------------------------------------------------
    template<typename A,typename B> 
        bool operator==(const Scalar<A> &a,const Scalar<B> &b)
    {
        typedef typename ComparisonTrait<A,B>::CompType CompType;
        CompType _a = convert_type<CompType>(a.value());
        CompType _b = convert_type<CompType>(b.value());

        return(_a == _b);
    }

    //--------------------------------------------------------------------------
    template<typename A,typename B> 
        bool operator==(const Scalar<A> &a,const B &b)
    {
        typedef typename ComparisonTrait<A,B>::CompType CompType;
        CompType _a = convert_type<CompType>(a.value());
        CompType _b = convert_type<CompType>(b);

        return (_a == _b);
    }

    //--------------------------------------------------------------------------
    template<typename A,typename B> 
        bool operator==(const A &a,const Scalar<B> &b)
    {
        typedef typename ComparisonTrait<A,B>::CompType CompType;
        CompType _a = convert_type<CompType>(a);
        CompType _b = convert_type<CompType>(b.value());

        return(_a==_b);
    }

    //--------------------------------------------------------------------------
    template<typename T> 
        bool operator!=(const Scalar<T> &a,const Scalar<T> &b)
    {
        if(a == b) return false;
        return true;
    }

    //--------------------------------------------------------------------------
    template<typename T> 
        bool operator!=(const T &a,const Scalar<T> &b)
    {
        if(a == b) return false;
        return true;
    }

    //--------------------------------------------------------------------------
    template<typename T> 
        bool operator!=(const Scalar<T> &a,const T &b)
    {
        if(a == b) return false;
        return true;
    }

    //--------------------------------------------------------------------------
    template<typename A,typename B> 
        bool operator!=(const Scalar<A> &a,const Scalar<B> &b)
    {
        typedef typename ComparisonTrait<A,B>::CompType CompType;
        CompType _a = convert_type<CompType>(a.value());
        CompType _b = convert_type<CompType>(b.value());

        return(_a != _b);
    }

    //--------------------------------------------------------------------------
    template<typename A,typename B> 
        bool operator!=(const Scalar<A> &a,const B &b)
    {
        typedef typename ComparisonTrait<A,B>::CompType CompType;
        CompType _a = convert_type<CompType>(a.value());
        CompType _b = convert_type<CompType>(b);

        return (_a != _b);
    }

    //--------------------------------------------------------------------------
    template<typename A,typename B> 
        bool operator!=(const A &a,const Scalar<B> &b)
    {
        return (a!=b.value());
    }

    //============================output operator=================================

    //overloaded output operator
    template<typename T> std::ostream &operator<<(std::ostream &o,
            const Scalar<T> &v) {

        if(v.name()!=""){
            o<<v.name()<<" = ";
        }
        o << v.value();
        if(v.unit() != ""){
            o<<" "<<v.unit();
        }

        if(v.description()!=""){
            o<<" ("<<v.description()<<")";
        }

        return o;
    }


    //===================binary addition operators==============================

    //! binary add operation
    template<typename A,typename B>
    Scalar<typename ResultTypeTrait<A,B>::AddResultType > 
    operator+(const Scalar<A> &a,const Scalar<B> &b)
    {
        typedef typename ResultTypeTrait<A,B>::AddResultType ResultType;
        Scalar<ResultType> o;

        ResultType _a = convert_type<ResultType>(a.value());
        ResultType _b = convert_type<ResultType>(b.value());

        o.value(_a + _b);

        return o;
    }

    //--------------------------------------------------------------------------
    template<typename A,typename B>
    Scalar<typename ResultTypeTrait<A,B>::AddResultType > 
    operator+(const Scalar<A> &a,const B &b)
    {
        typedef typename ResultTypeTrait<A,B>::AddResultType ResultType;
        Scalar<ResultType> o;

        ResultType _a = convert_type<ResultType>(a.value());
        ResultType _b = convert_type<ResultType>(b);

        o.value(_a + _b);
        return o;
    }

    //--------------------------------------------------------------------------
    template<typename A,typename B>
    Scalar<typename ResultTypeTrait<A,B>::AddResultType > 
    operator+(const A &a,const Scalar<B> &b)
    {
        typedef typename ResultTypeTrait<A,B>::AddResultType ResultType;
        Scalar<ResultType> o;

        ResultType _a = convert_type<ResultType>(a);
        ResultType _b = convert_type<ResultType>(b.value());

        o.value(_a + _b);

        return o;
    }

    //======================Binary subtraction operator=========================
    //overloaded subtraction operator
    template<typename A,typename B>
    Scalar<typename ResultTypeTrait<A,B>::SubResultType > 
    operator-(const Scalar<A> &a, const Scalar<B> &b) 
    {
        typedef typename ResultTypeTrait<A,B>::SubResultType ResultType;
        Scalar<ResultType> tmp;

        ResultType _a = convert_type<ResultType>(a.value());
        ResultType _b = convert_type<ResultType>(b.value());

        tmp.value(_a - _b);

        return tmp;
    }

    //--------------------------------------------------------------------------
    template<typename A,typename B>
    Scalar<typename ResultTypeTrait<A,B>::SubResultType > 
    operator-(const A& a, const Scalar<B> &b) 
    {
        typedef typename ResultTypeTrait<A,B>::SubResultType ResultType;
        Scalar<ResultType> tmp;

        ResultType _a = convert_type<ResultType>(a);
        ResultType _b = convert_type<ResultType>(b.value());

        tmp.value(_a - _b);

        return tmp;
    }

    //--------------------------------------------------------------------------
    template<typename A,typename B>
    Scalar<typename ResultTypeTrait<A,B>::SubResultType > 
    operator-(const Scalar<A> &a, const B &b) 
    {
        typedef typename ResultTypeTrait<A,B>::SubResultType ResultType;
        Scalar<ResultType> tmp;

        ResultType _a = convert_type<ResultType>(a.value());
        ResultType _b = convert_type<ResultType>(b);

        tmp.value(_a - _b);
        return tmp;
    }

    //======================Binary multiplication operator======================
    //overloading the multiplication operator
    template<typename A,typename B>
    Scalar<typename ResultTypeTrait<A,B>::MultResultType > 
    operator*(const Scalar<A> &a, const Scalar<B> &b) 
    {
        typedef typename ResultTypeTrait<A,B>::MultResultType ResultType;
        Scalar<ResultType> tmp;

        ResultType _a = convert_type<ResultType>(a.value());
        ResultType _b = convert_type<ResultType>(b.value());

        tmp.value(_a * _b);
        return tmp;
    }

    //--------------------------------------------------------------------------
    template<typename A,typename B>
    Scalar<typename ResultTypeTrait<A,B>::MultResultType > 
    operator*(const A& a, const Scalar<B> &b) 
    {
        typedef typename ResultTypeTrait<A,B>::MultResultType ResultType;
        Scalar<ResultType> tmp;

        ResultType _a = convert_type<ResultType>(a);
        ResultType _b = convert_type<ResultType>(b.value());

        tmp.value(_a * _b);
        return tmp;
    }

    //--------------------------------------------------------------------------
    template<typename A,typename B>
    Scalar<typename ResultTypeTrait<A,B>::MultResultType > 
    operator*(const Scalar<A> &a, const B& b) 
    {
        typedef typename ResultTypeTrait<A,B>::MultResultType ResultType;
        Scalar<ResultType> tmp;

        ResultType _a = convert_type<ResultType>(a.value());
        ResultType _b = convert_type<ResultType>(b);

        tmp.value(_a * _b);
        return tmp;
    }

    //===================Binary division operator===============================
    //overloading the division operator
    template<typename A,typename B>
    Scalar<typename ResultTypeTrait<A,B>::DivResultType > 
    operator/(const Scalar<A> &a, const Scalar<B> &b) 
    {
        typedef typename ResultTypeTrait<A,B>::DivResultType ResultType;
        Scalar<ResultType> tmp;

        ResultType _a = convert_type<ResultType>(a.value());
        ResultType _b = convert_type<ResultType>(b.value());

        tmp.value(_a / _b);
        return tmp;
    }

    //--------------------------------------------------------------------------
    template<typename A,typename B>
    Scalar<typename ResultTypeTrait<A,B>::DivResultType > 
    operator/(const A& a, const Scalar<B> &b) 
    {
        typedef typename ResultTypeTrait<A,B>::DivResultType ResultType;
        Scalar<ResultType> tmp;

        ResultType _a = convert_type<ResultType>(a);
        ResultType _b = convert_type<ResultType>(b.value());

        tmp.value(_a / _b);
        return tmp;
    }

    //--------------------------------------------------------------------------
    template<typename A,typename B>
    Scalar<typename ResultTypeTrait<A,B>::DivResultType > 
    operator/(const Scalar<A> &a, const B &b) 
    {
        typedef typename ResultTypeTrait<A,B>::DivResultType ResultType;
        Scalar<ResultType> tmp;

        ResultType _a = convert_type<ResultType>(a.value());
        ResultType _b = convert_type<ResultType>(b);

        tmp.value(_a / _b);
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
