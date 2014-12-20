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

#include <pni/core/types/type_utils.hpp>
#include <pni/core/types/type_conversion.hpp>
#include <pni/core/types/unchecked_convertible.hpp>

#include <map>

namespace pni{
namespace core{
    typedef std::vector<type_id_t> type_vector; 

    template<typename T>
    std::pair<type_id_t,type_vector> generate_map_element()
    {
        typedef typename boost::mpl::at<unchecked_type_vectors,T>::type vector_t;
        
        return {type_id_map<T>::type_id,
                build_type_id_container<type_vector,vector_t>()};

    }
    

    static const std::map<type_id_t,type_vector> conversion_map{
        generate_map_element<uint8>(),
        generate_map_element<uint16>(),
        generate_map_element<uint32>(),
        generate_map_element<uint64>(),
        generate_map_element<int8>(),
        generate_map_element<int16>(),
        generate_map_element<int32>(),
        generate_map_element<int64>(),
        generate_map_element<float32>(),
        generate_map_element<float64>(),
        generate_map_element<float128>(),
        generate_map_element<complex32>(),
        generate_map_element<complex64>(),
        generate_map_element<complex128>()
    };



    bool is_unchecked_convertible(type_id_t source_tid,type_id_t target_tid)
    {
        type_vector types = conversion_map.at(source_tid);
        
        return std::count(types.begin(),types.end(),target_tid);
    }


//end of namespace
}
}

