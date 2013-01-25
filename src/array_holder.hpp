/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: 11 08, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "array_holder_interface.hpp"

namespace pni{
namespace core{

    template<typename ATYPE> const void *get_pointer(const ATYPE &a)
    {
        return (void *)(a.storage().ptr());
    }

    template<typename ATYPE> const void *get_pointer(const numarray<ATYPE> &a)
    {
        return (void *)(a.storage().storage().ptr());
    }

    template<typename OT> class array_holder:public array_holder_interface
    {
        private:
            OT _object; //!< the original object 
        public:
            //==================constructors and destructor====================
            //construct by copying o
            array_holder(const OT &o):_object(o) {}

            //-----------------------------------------------------------------
            //construct by moving o
            array_holder(OT &&o):_object(std::move(o)) {}

            //-----------------------------------------------------------------
            //copy constructor
            array_holder(const array_holder<OT> &o):
                _object(o._object) 
            {}

            //-----------------------------------------------------------------
            //move constructor
            array_holder(array_holder<OT> &&o):
                _object(std::move(o._object)) 
            {}

            virtual array_holder_interface *clone() const 
            {
                return new array_holder<OT>(_object);
            }

            //====================public member functions======================
            virtual type_id_t type_id() const{ return OT::type_id; }
            
            //-----------------------------------------------------------------
            virtual size_t rank() const { return _object.rank(); }

            //-----------------------------------------------------------------
            virtual shape_t shape() const 
            {
                return _object.template shape<shape_t>();
            }

            //-----------------------------------------------------------------
            virtual size_t size() const { return _object.size(); }

            //-----------------------------------------------------------------
            virtual value operator[](size_t i) const
            {
                return value(_object[i]);
            }

            //-----------------------------------------------------------------
            virtual value_ref operator[](size_t i) 
            {
                return value_ref(std::ref(_object[i]));
            }

            //-----------------------------------------------------------------
            virtual value at(size_t i) const 
            {
                return value(_object.at(i));
            }

            //-----------------------------------------------------------------
            virtual value_ref at(size_t i) 
            {
                return value_ref(std::ref(_object.at(i)));
            }

            //-----------------------------------------------------------------
            virtual std::ostream &write(std::ostream &os) const 
            {
                os<<_object;

                return os;
            }

            //-----------------------------------------------------------------
            virtual std::istream &read(std::istream &is) 
            {
                is>>_object; 

                return is;
            }

            //-----------------------------------------------------------------
            virtual string type_name() const
            {
                return typeid(OT).name();
            }

            //-----------------------------------------------------------------
            virtual const void *ptr() const
            {
                return get_pointer(_object);            
            }

    };

//end of namespace
}
}
