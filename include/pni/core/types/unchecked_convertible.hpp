//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
//  Created on: Dec 18, 2014
//      Author: Eugen Wintersberger
//
#pragma once

#include <boost/mpl/pair.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/at.hpp>
#include "types.hpp"

namespace pni{
namespace core{

    using namespace boost;

    //!
    //! \ingroup type_classes_internal
    //! \brief unchecked convertible map
    //! 
    //! This map provides for each type a list of types to which this type 
    //! can be converted without range checking. 
    typedef mpl::map<
        //-------------source type uint8--------------------------------------
        mpl::pair<
                  uint8,
                  mpl::vector<uint8,uint16,uint32,uint64,
                              int16,int32,int64,
                              float32,float64,float128,
                              complex32,complex64,complex128>
                 >,

        //----------------source type uint16----------------------------------
        mpl::pair<
                  uint16,
                  mpl::vector<uint16,uint32,uint64, 
                              int32,int64,
                              float32,float64,float128,
                              complex32,complex64,complex128>
                >,

        //----------------------source type uint32----------------------------
        mpl::pair<
                  uint32,
                  mpl::vector<uint32,uint64,
                              int64,
                              float32,float64,float128,
                              complex32,complex64,complex128>
                >,

        //--------------------------source type uint64------------------------
        mpl::pair<
                  uint64,
                  mpl::vector<uint64,
                              float32,float64,float128,
                              complex32,complex64,complex128>
                >,

        //------------------------source type int8 ---------------------------
        mpl::pair<
                  int8,
                  mpl::vector<int8,int16,int32,int64,
                              float32,float64,float128,
                              complex32,complex64,complex128>
                >,

        //-----------------------source type int16----------------------------
        mpl::pair<
                  int16,
                  mpl::vector<int16,int32,int64,
                              float32,float64,float128,
                              complex32,complex64,complex128>
                >,

        //------------------------source type int32---------------------------
        mpl::pair<
                  int32,
                  mpl::vector<int32,int64,
                              float32,float64,float128,
                              complex32,complex64,complex128>
                >,

        //------------------------source type int64----------------------------
        mpl::pair<
                  int64,
                  mpl::vector<int64,
                             float32,float64,float128,
                             complex32,complex64,complex128>
                >,

        //-------------------------source type float32------------------------
        mpl::pair<
                  float32,
                  mpl::vector<float32,float64,float128,
                              complex32,complex64,complex128>
                 >,

        //-------------------------source type float64------------------------
        mpl::pair<
                  float64,
                  mpl::vector<float64,float128,complex64,complex128>
                 >,

        //-------------------source type float128-----------------------------
        mpl::pair<float128,mpl::vector<float128,complex128>>,

        //-------------------source type complex32----------------------------
        mpl::pair<complex32,mpl::vector<complex32,complex64,complex128>>,
        
        //-------------------source type complex64----------------------------
        mpl::pair<complex64,mpl::vector<complex64,complex128>>,

        //-------------------source type complex128---------------------------
        mpl::pair<complex128,mpl::vector<complex128>>

        > unchecked_type_vectors;

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief check if a type is unchecked convertible
    //!
    //! This template provides information about if a type can be converted
    //! to another without having the range checked. 
    //! 
    //! \tparam ST source type
    //! \tparam TT target type
    template<
             typename ST,
             typename TT
            >
    struct unchecked_convertible
    {
        //select the type vector
        typedef typename mpl::at<unchecked_type_vectors,ST>::type map_element;
        typedef mpl::contains<map_element,TT> c;
        static const bool value = c::value;
    };






//end of namespace
}
}
