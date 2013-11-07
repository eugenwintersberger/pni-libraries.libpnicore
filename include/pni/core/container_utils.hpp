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
 * Created on: Nov 07, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <iostream>
#include <sstream>
#include "exceptions.hpp"

namespace pni{
namespace core{

    /*!
    \ingroup util_classes
    \brief container utility

    Container play a crucial role in libpnicore. In particular those provided by
    the STL.  This class provides common creation functions for all container
    types used within libpnicore.  There are virtually three kinds of containers
    currently availble 

    \li std::vector
    \li std::list 
    \li std::array

    While for former two can be treated more ore less in the same way std::array
    requires some extra work. This class provides creation function for the
    first two containers. A special overload exists for std::array.
    */
    template<typename CTYPE> struct container_utils
    {
        //! type of the container 
        typedef CTYPE container_type;
        //! the element type of the container
        typedef typename CTYPE::value_type value_type;

        //---------------------------------------------------------------------
        /*!
        \brief create container of given size

        Create a new container with a size of n elements.
        \code
        typedef std::list<string> list_type;
        typedef std::vector<float64> vector_type;

        auto v = container_utils<vector_type>::create(20);
        auto l = container_utils<list_type>::create(20);
        \endcode
        
        \param n number of elements
        \param default_value the default value for the elements
        \return instance of container type of size n
        */
        static container_type create(size_t n,value_type default_value=value_type())
        {
            container_type c(n);
            std::fill(c.begin(),c.end(),default_value);
            return c;
        }

        //---------------------------------------------------------------------
        /*!
        \brief create container from a range

        Create a new container from a pair of iterators. 
        \code
        typedef std::list<string> list_type;
        typedef std::vector<float64> vector_type;

        .... c = ....; //an arbitrary STL compliant container
        auto v = container_utils<vector_type>::create(c.begin(),c.end());
        auto l = container_utils<list_type>::create(c.begin(),c.end());
        \endcode

        \tparam ITERT iterator type
        \param begin iterator to the first element
        \param end iterator to the last element
        \return instance of container_type
        */
        template<typename ITERT,
                 typename = typename std::enable_if<
                 !std::is_pod<ITERT>::value
                 >::type
                >
        static container_type create(ITERT begin,ITERT end)
        {
            container_type c(std::distance(begin,end));
            std::copy(begin,end,c.begin());
            return c;
        }

        //---------------------------------------------------------------------
        /*!
        \brief create from another container

        Create a new container from an arbitrary container provided by the use. 
        \code
        typedef std::list<string> list_type;
        typedef std::vector<float64> vector_type;

        .... c = ....; //an arbitrary STL compliant container
        auto v = container_utils<vector_type>::create(c);
        auto l = container_utils<list_type>::create(c);
        \endcode

        \tparam OCTYPE type of the source container
        \param o reference to the original container
        \return instance of container_type with data from o
        */
        template<typename OCTYPE,
                 typename = typename std::enable_if<
                 !std::is_pod<OCTYPE>::value
                 >::type
                >
        static container_type create(const OCTYPE &o)
        {
            container_type c(o.size());
            std::copy(o.begin(),o.end(),c.begin());
            return c;
        }

        //---------------------------------------------------------------------
        /*!
        \brief create from initializer list

        As construction from an initializer list is not an issue for the
        container types treated by this class this function is provided for
        convienance in order to expose a common interface.

        \code 
        typedef std::list<string> list_type;
        typedef std::vector<float64> vector_type;

        auto v = container_utils<vector_type>::create({1,2,3,4});
        auto l = container_utils<list_type>::create({1,2,3,4});
        \endcode

        \tparam T element type of the initializer list
        \pararm list initializer list instance
        \return container with data from initializer list
        */
        template<typename T>
        static container_type create(const std::initializer_list<T> &list)
        {
            container_type c(list.size());
            std::copy(list.begin(),list.end(),c.begin());
            return c;
        }


    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup util_classes
    \brief container utility for std::array

    While std::vector and std::list are dynamic types whose size can be set at
    compile time, the size of std::array is fixed at compile time. 
    Therefore, std::array requires some special treatment for array
    construction. This specialization of the container_utils takes care about
    all the peculiarities of std::array.
    */
    template<typename T,size_t N> struct container_utils<std::array<T,N>>
    {
        //! type of the container
        typedef std::array<T,N> container_type;
        //! value type of the container
        typedef T value_type;

        //---------------------------------------------------------------------
        /*!
        \brief create a container of size n

        Here we try to create a container of size n and initialize all elements
        with default_value. As n for std::array is already defined at compile
        time this method does not allocate new memory. If n does not match the
        size of std::array an exception will be thrown. Otherwise std::array
        will be initialized with default_value. 

        \code 
        typedef std::array<float64,3> array_type; 

        auto vector = container_utils<array_type>::create(3,1.23);
        \endcode

        \throws size_mismatch_error if n does not match the size of std::array
        \param n number of elements
        \param default_value the default value for the array
        \return instance of std::array
        */
        static container_type create(size_t n,value_type default_value=value_type())
        {
            if(n!=N)
            {
                std::stringstream message;
                message<<"Number of elements ("<<n<<") not supported by ";
                message<<"array type which has ("<<N<<")!";
                throw size_mismatch_error(EXCEPTION_RECORD,message.str());
            }

            container_type v;
            std::fill(v.begin(),v.end(),default_value);
            return v;
        }

        //---------------------------------------------------------------------
        /*!
        \brief initialize std::array from an iterator range

        Initilize an instance of std::array from an iterator range. If the
        number of elemenst spanned by the iterator range does not match the
        number of elements in std::array an exception will be thrown. Otherwise,
        an instance of std::array initialized with the data refered to by the
        iterator range will be returned. 

        \code
        typedef std::array<float64,3> array_type;

        ... c = ...; //some container type
        auto vector = container_utils<array_type>::create(c.begin(),c.end());
        \endcode

        \throws size_mismatch_error if the number of elements spanned by the
        iterator range does not match the size of the array
        \tparam ITERT iterator type
        \param begin iterator to the first element
        \param end iterator to the last+1 element
        \return initialized instance of std::array
        */
        template<typename ITERT,
                 typename = typename std::enable_if<
                 !std::is_pod<ITERT>::value
                 >::type
                >
        static container_type create(ITERT begin,ITERT end)
        {
            if(N!=std::distance(begin,end))
            {
                std::stringstream message;
                message<<"Iterators span ("<<std::distance(begin,end)<<")";
                message<<" only ("<<N<<") supported by the array type!";
                throw size_mismatch_error(EXCEPTION_RECORD,message.str());
            }

            container_type v;
            std::copy(begin,end,v.begin());
            return v;
        }

        //---------------------------------------------------------------------
        /*!
        \brief initialize std::array from a container

        Here we initialize an instance of std::array from an arbitrary, STL
        compliant container. If the size of the container does not match the
        size of std::array an exception will be thrown. 

        \code 
        typedef std::array<float64,3> array_type;

        auto vector = container_utils<array_type>::create(c);
        \endcode

        \throws size_mismatch_error if the container size does not match the
        array size
        \param o reference to the original container
        \return initialized instance of OCTYPE
        */
        template<typename OCTYPE,
                 typename = typename std::enable_if<
                 !std::is_pod<OCTYPE>::value
                 >::type
                >
        static container_type create(const OCTYPE &o)
        {
           if(o.size() != N)
           {
               std::stringstream message;
               message<<"Original container has ("<<o.size()<<") elements, ";
               message<<"array supports only ("<<N<<")!";
               throw size_mismatch_error(EXCEPTION_RECORD,message.str());
           }

           container_type v;
           std::copy(o.begin(),o.end(),v.begin());
           return v;
        }

        //---------------------------------------------------------------------
        /*!
        \brief initialize std::array from an initializer list

        The syntax of how instances of std::array are constructed from
        initializer lists differes from that of std::vector and std::list. This
        function provides a common interface. If the number of elements in the
        initializer list does not match that of the std::array instance an
        exception will be thrown.

        \code 
        typedef std::array<float64,3> array_type;

        auto v = container_utils<array_type>::create({1,2,3});
        \endcode

        \throws size_mismatch_error if the size of std::array and the
        initializer list do not match
        \tparam T element type of the initializer list
        \param list initializer list
        \return initialized instance of std::array
        */
        template<typename ET>
        static container_type create(const std::initializer_list<ET> &list)
        {
            if(list.size()!=N)
            {
                std::stringstream message;
                message<<"Initializer list has ("<<list.size()<<") elements, ";
                message<<"array supports only ("<<N<<")!";
                throw size_mismatch_error(EXCEPTION_RECORD,message.str());
            }

            container_type v;
            std::copy(list.begin(),list.end(),v.begin());
            return v;
        }

        
    };


//end of namespace
}
}
