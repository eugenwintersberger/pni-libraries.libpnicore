/*
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
 * Created on: Jul 25,2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#ifndef __MULT_HPP__
#define __MULT_HPP__

#include "OpTraits.hpp"

#include "../Iterator.hpp"
#include "../NumArray.hpp"


namespace pni{
namespace utils{


    /*!
    \ingroup numeric_array_classes
    \brief Multiplication expression template

    */
    template<typename OP1T,typename OP2T> class Mult
    {
        private:
            //! left operand
            typename OpTrait<OP1T>::ref_type _op1;
            //! right operand
            typename OpTrait<OP2T>::ref_type _op2;
        public:
            //--------------------public types---------------------------------
            //! value type of the multiplication
            typedef typename OP1T::value_type value_type;
            //! type of the operation class
            typedef Mult<OP1T,OP2T> array_type;
            //! storage type
            typedef void storage_type;
            //! non-const iterator type - this is only to satsify the interaface
            typedef Iterator<array_type,0> iterator; 
            //! const iterator type
            typedef Iterator<array_type,1> const_iterator;

            //===================constructors==================================
            /*! constructor

            Set up the operator class.
            \param o1 left operand
            \param o2 right operand
            */
            Mult(const OP1T &o1,const OP2T &o2):
                _op1(o1),
                _op2(o2)
            {}

            //====================public methods===============================
            /*! 
            \brief get value at index i

            Return the value of _op1[i]*_op2[i];
            \param i index for which to reqest data
            \return result of operation
            */
            value_type operator[](size_t i) const
            {
                return this->_op1[i]*this->_op2[i];
            }

            //-----------------------------------------------------------------
            /*! 
            \brief return size of the operator

            This is the maximum size of the two operands.
            \return size of the operation
            */
            size_t size() const
            {
                return _op1.size()>_op2.size() ? _op1.size() : _op2.size();
            }

            //=====================iterators===================================
            //! get iterator on first element
            const_iterator begin() const
            {
                return const_iterator(this,0);
            }

            //-----------------------------------------------------------------
            //! get iterator on last+1 element
            const_iterator end() const
            {
                return const_iterator(this,this->size());
            }

    };

    //========================implementation of operators======================

    /*!
    \ingroup numeric_array_classes
    \brief multiplication operator

    Expression template operator for the multiplication of two instances of 
    the NumArray template.
    \tparam AT1 storage type of left operand
    \tparam AT2 storage type of right operand
    \param a left operand
    \param b right operand
    \return instance of NumArray with result
    */
    template<typename AT1,typename AT2>
    NumArray<Mult<NumArray<AT1>,NumArray<AT2> > >
    operator*(const NumArray<AT1> &a,const NumArray<AT2> &b)
    {
        typedef Mult<NumArray<AT1>,NumArray<AT2> > op_type;
        return NumArray<op_type>(op_type(a,b));
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup numeric_array_classes
    \brief multiplication operator

    Expression template operator for the multiplication of an instance of
    NumArray with a scalar. 
    \tparam AT storage type of the NumArray instance
    \param a left operand (array type)
    \param b right operand (scalar)
    \return instance of NumArray with result
    */
    template<typename AT>
    NumArray<Mult<NumArray<AT>,Scalar<typename AT::value_type> > >
    operator*(const NumArray<AT> &a,typename AT::value_type const &b)
    {
        typedef NumArray<AT> atype;
        typedef Scalar<typename AT::value_type> stype;
        typedef Mult<atype,stype> op_type;
        return NumArray<op_type>(op_type(a,stype(b)));
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup numeric_array_classes
    \brief multiplication operator

    Expression template operator for the multiplication of an instance of
    NumArray and a scalar.
    \tparam AT storage type for the NumArray instance
    \param a left operand (scalar value)
    \param b right operand (array type)
    \return NumArray instance representing the result
    */
    template<typename AT>
    NumArray<Mult<Scalar<typename AT::value_type>,NumArray<AT> > >
    operator*(typename AT::value_type const &a,const NumArray<AT> &b)
    {
        typedef NumArray<AT> atype;
        typedef Scalar<typename AT::value_type> stype;
        typedef Mult<stype,atype> op_type;
        return NumArray<op_type>(op_type(stype(a),b));
    }


//end of namespace
}
}

#endif
