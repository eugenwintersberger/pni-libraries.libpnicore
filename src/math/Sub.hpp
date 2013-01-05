/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Jul 25,2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "OpTraits.hpp"

#include "../Iterator.hpp"

namespace pni{
namespace core{
    
    template<typename ATYPE> class ArrayView;

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
            //! view type
            typedef ArrayView<array_type> view_type;

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

            /*! 
            \brief get the shape

            Return the shape of the expression template. This both operands are
            instances of NumArray we can return the shape of one of the arrys. 
            If both are scalars we return the shape of the scalar. If one is
            scalar and one is an array the array type wins.
            \return shape of the operation
            */
            template<typename CTYPE> CTYPE shape() const
            {

                //_op1  is a scalar
                if(_op1.rank()==0)
                {
                    //if _op2 is an array 
                    if(_op2.rank() != 0) return _op2.template shape<CTYPE>();
                }
                //in all other cases we do not care what type _op2 is 
                //we just return the shape of _op1
                return  _op1.template shape<CTYPE>();
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
