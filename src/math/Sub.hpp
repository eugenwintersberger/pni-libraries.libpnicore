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
#ifndef __SUB_HPP__
#define __SUB_HPP__

#include "OpTraits.hpp"

#include "../Iterator.hpp"


namespace pni{
namespace utils{


    /*! 
    \ingroup numeric_array_classes
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


//end of namespace
}
}

#endif
