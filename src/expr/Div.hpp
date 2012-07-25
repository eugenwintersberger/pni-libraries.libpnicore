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
#ifndef __DIV_HPP__
#define __DIV_HPP__

#include "OpTraits.hpp"

#include "../Iterator.hpp"
#include "../NumArray.hpp"


namespace pni{
namespace utils{


    template<typename OP1T,typename OP2T> class Div
    {
        private:
            typename OpTrait<OP1T>::ref_type _op1;
            typename OpTrait<OP2T>::ref_type _op2;
        public:
            //--------------------public types---------------------------------
            typedef typename OP1T::value_type value_type;
            typedef Div<OP1T,OP2T> array_type;
            typedef void storage_type;
            typedef Iterator<array_type,0> iterator;
            typedef Iterator<array_type,1> const_iterator;

            //===================constructors==================================
            Div(const OP1T &o1,const OP2T &o2):
                _op1(o1),
                _op2(o2)
            {}

            //====================public methods===============================
            value_type operator[](size_t i) const
            {
                return this->_op1[i]/this->_op2[i];
            }

            //-----------------------------------------------------------------
            size_t size() const
            {
                return _op1.size()>_op2.size() ? _op1.size() : _op2.size();
            }

            //=====================iterators===================================
            const_iterator begin() const
            {
                return const_iterator(this,0);
            }

            //-----------------------------------------------------------------
            const_iterator end() const
            {
                return const_iterator(this,this->size());
            }

    };

    //========================implementation of operators======================

    //operator
    template<typename AT1,typename AT2>
    NumArray<Div<NumArray<AT1>,NumArray<AT2> > >
    operator/(const NumArray<AT1> &a,const NumArray<AT2> &b)
    {
        typedef Div<NumArray<AT1>,NumArray<AT2> > op_type;
        return NumArray<op_type>(op_type(a,b));
    }

    //-------------------------------------------------------------------------
    template<typename AT>
    NumArray<Div<NumArray<AT>,Scalar<typename AT::value_type> > >
    operator/(const NumArray<AT> &a,typename AT::value_type const &b)
    {
        typedef NumArray<AT> atype;
        typedef Scalar<typename AT::value_type> stype;
        typedef Div<atype,stype> op_type;
        return NumArray<op_type>(op_type(a,stype(b)));
    }

    //-------------------------------------------------------------------------
    template<typename AT>
    NumArray<Div<Scalar<typename AT::value_type>,NumArray<AT> > >
    operator/(typename AT::value_type const &a,const NumArray<AT> &b)
    {
        typedef NumArray<AT> atype;
        typedef Scalar<typename AT::value_type> stype;
        typedef Div<stype,atype> op_type;
        return NumArray<op_type>(op_type(stype(a),b));
    }


//end of namespace
}
}

#endif
