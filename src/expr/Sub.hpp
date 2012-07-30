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
#ifndef __ADD_HPP__
#define __ADD_HPP__

#include "OpTraits.hpp"

#include "../Iterator.hpp"
#include "../NumArray.hpp"


namespace pni{
namespace utils{


    /*! 
    \ingroup data_classes
    \brief subtraction expression template

    Expression template for subtraction of array templates.
    \tparam OP1T left operand type
    \tparam OP2T right operand type
    */
    template<typename OP1T,typename OP2T> class Sub
    {
        private:
            //! reference to the left operand
            typename OpTrait<OP1T>::ref_type _op1;
            //! reference to the right operand
            typename OpTrait<OP2T>::ref_type _op2;
        public:
            //--------------------public types---------------------------------
            //! type of the element 
            typedef typename OP1T::value_type value_type;
            //! type of the template
            typedef Sub<OP1T,OP2T> array_type;
            //! storage type - not used for this
            typedef void storage_type;
            //! iterator type
            typedef Iterator<array_type,0> iterator;
            //! const iterator type
            typedef Iterator<array_type,1> const_iterator;

            //===================constructors==================================
            //! standard constructor
            Sub(const OP1T &o1,const OP2T &o2):
                _op1(o1),
                _op2(o2)
            {}

            //====================public methods===============================
            //! get value i
            value_type operator[](size_t i) const
            {
                return this->_op1[i]-this->_op2[i];
            }

            //-----------------------------------------------------------------
            //! get size of the 
            size_t size() const
            {
                return _op1.size()>_op2.size() ? _op1.size() : _op2.size();
            }

            //=====================iterators===================================
            //! get const iterator to the first element
            const_iterator begin() const
            {
                return const_iterator(this,0);
            }

            //-----------------------------------------------------------------
            //! get const iterator to the last element
            const_iterator end() const
            {
                return const_iterator(this,this->size());
            }

    };

    //========================implementation of operators======================

    //operator
    template<typename AT1,typename AT2>
    NumArray<Sub<NumArray<AT1>,NumArray<AT2> > >
    operator-(const NumArray<AT1> &a,const NumArray<AT2> &b)
    {
        typedef Sub<NumArray<AT1>,NumArray<AT2> > op_type;
        return NumArray<op_type>(op_type(a,b));
    }

    //-------------------------------------------------------------------------
    template<typename AT>
    NumArray<Sub<NumArray<AT>,Scalar<typename AT::value_type> > >
    operator-(const NumArray<AT> &a,typename AT::value_type const &b)
    {
        typedef NumArray<AT> atype;
        typedef Scalar<typename AT::value_type> stype;
        typedef Sub<atype,stype> op_type;
        return NumArray<op_type>(op_type(a,stype(b)));
    }

    //-------------------------------------------------------------------------
    template<typename AT>
    NumArray<Sub<Scalar<typename AT::value_type>,NumArray<AT> > >
    operator-(typename AT::value_type const &a,const NumArray<AT> &b)
    {
        typedef NumArray<AT> atype;
        typedef Scalar<typename AT::value_type> stype;
        typedef Sub<stype,atype> op_type;
        return NumArray<op_type>(op_type(stype(a),b));
    }


//end of namespace
}
}

#endif
