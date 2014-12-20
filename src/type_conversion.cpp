//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// 
// ===========================================================================
//
//  Created on: Dec 19, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/types/type_conversion.hpp>
#include <pni/core/types/unchecked_convertible.hpp>

namespace pni{
namespace core{

    bool is_unchecked_convertible(type_id_t source_tid,type_id_t target_tid)
    {
        if(source_tid == type_id_t::UINT8)
            return is_unchecked_convertible_to<uint8>(target_tid);
        else if(source_tid == type_id_t::INT8)
            return is_unchecked_convertible_to<int8>(target_tid);
        else if(source_tid == type_id_t::UINT16)
            return is_unchecked_convertible_to<uint16>(target_tid);
        else if(source_tid == type_id_t::INT16)
            return is_unchecked_convertible_to<int16>(target_tid);
        else if(source_tid == type_id_t::UINT32)
            return is_unchecked_convertible_to<uint32>(target_tid);
        else if(source_tid == type_id_t::INT32)
            return is_unchecked_convertible_to<int32>(target_tid);
        else if(source_tid == type_id_t::UINT64)
            return is_unchecked_convertible_to<uint64>(target_tid);
        else if(source_tid == type_id_t::INT64)
            return is_unchecked_convertible_to<int64>(target_tid);
        else if(source_tid == type_id_t::FLOAT32)
            return is_unchecked_convertible_to<float32>(target_tid);
        else if(source_tid == type_id_t::FLOAT64)
            return is_unchecked_convertible_to<float64>(target_tid);
        else if(source_tid == type_id_t::FLOAT128)
            return is_unchecked_convertible_to<float128>(target_tid);
        else if(source_tid == type_id_t::COMPLEX32)
            return is_unchecked_convertible_to<complex32>(target_tid);
        else if(source_tid == type_id_t::COMPLEX64)
            return is_unchecked_convertible_to<complex64>(target_tid);
        else if(source_tid == type_id_t::COMPLEX128)
            return is_unchecked_convertible_to<complex128>(target_tid);
        else 
            return false;
    }

//end of namespace
}
}
