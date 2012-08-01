#ifndef __ARRAYSELECTION_HPP__
#define __ARRAYSELECTION_HPP__

#include <vector>
#include <algorithm>

#include "ExceptionUtils.hpp"
#include "Slice.hpp"

namespace pni{
namespace utils{

    /*! 
    \ingroup index_mapping_classes
    \brief selection from a multidimensional array

    This type represents the selection of elements from a multidimensional
    array and is primarily used by the ArrayView template. 
    Its primary purpose is to map selection indices to indices of the
    original array. This is required as a selection might does not have the same
    rank as the original array. Consider an array of shape (4,10,28) from which
    we select (1,10,28). The effective rank of this selection is 2 while that of
    the original array would be 3. Additionally, such a selection would have the
    effective rank (10,28) as the first index can be omitted. This allows to
    select data of a particular dimensionality from an array of arbitrary rank.
    The only assumption that must be made is that the rank of the original array
    is larger than that of the required selection. 
    Clearly, one wants to use a two dimensional index (i,j) to address an
    element in the selection. However, to get the data from the original array
    this must be modified to (1,i,j) which is the major purpose of this type.
    */
    class ArraySelection
    {
        private:
            //member variables describing the selection in the original array
            //all of these containers have the same size which is equal to the
            //rank of the original array
            //! shape of the selection in the original array
            std::vector<size_t> _oshape;             
            //! offset in the original array
            std::vector<size_t> _offset;
            //! stride in the original array
            std::vector<size_t> _stride;

            //member variables describing the effective shape and rank of the 
            //selection
            size_t _rank;   //!< effective rank of the selection
            std::vector<size_t> _shape; //!< effective shape of the selection
            size_t _size; //!< effective size of the selection

            //! setup selection parameters
            void _set_local_params()
            {
                _rank = 0;
                _shape = std::vector<size_t>(0);
                _size = 1;
                for(auto ositer=_oshape.begin(),
                         oiter=_offset.begin(),
                         siter=_stride.begin();
                    ositer != _oshape.end();
                    ++ositer,++oiter,++siter)
                {
                    if((*ositer)!=1)
                    {
                        _rank++;
                        
                        //need to determine the number of indices here
                        size_t s = *ositer;
                        _shape.push_back(s);
                        _size *= s;
                    }
                }
            }

        public:
            //===================constructors and destructor====================
            //! default constructor
            ArraySelection():
                _oshape(0),
                _offset(0),
                _stride(0),
                _rank(0),
                _shape(0),
                _size(0)
            {}

            //------------------------------------------------------------------
            //! standard constructor
            template<template<typename ...> class CTYPE,typename ...OTS>
            explicit ArraySelection(const CTYPE<OTS...> &oshape,
                                    const CTYPE<OTS...> &ooffset,
                                    const CTYPE<OTS...> &ostride):
                _oshape(oshape.size()),
                _offset(ooffset.size()),
                _stride(ostride.size())
            {
                std::copy(oshape.begin(),oshape.end(),_oshape.begin());
                std::copy(ooffset.begin(),ooffset.end(),_offset.begin());
                std::copy(ostride.begin(),ostride.end(),_stride.begin());

                _set_local_params();
            }

            //-----------------------------------------------------------------
            //! copy constructor
            ArraySelection(const ArraySelection &s);

            //-----------------------------------------------------------------
            //! move constructor
            ArraySelection(ArraySelection &&s);

            //-----------------------------------------------------------------
            //! static creation function
            static ArraySelection create(const std::vector<Slice> &s);

            //=====================assignment operators========================
            //! copy assignment operator
            ArraySelection &operator=(const ArraySelection &s);

            //-----------------------------------------------------------------
            //! move assignment operator
            ArraySelection &operator=(ArraySelection &&s);
           
            //=================inquery methods=================================
            //! get rank of the selection
            size_t rank() const { return _rank; }

            //! get shape of the selection
            const std::vector<size_t> &shape() const { return _shape; }

            //! get size
            size_t size() const { return _size; }


            //================get indices======================================
            /*! 
            \brief compute original index

            The functionality of this template method can be best explained
            using an example. 
            \code
            typedef std::vector<size_t> itype;

            //create a (1,25,128) selection from a 3D array at offset (1,1,1)
            //and with stride (1,1,1)
            ArraySelection s(itype{1,25,128},itype{1,1,1},itype{1,1,1});

            //selection index
            itype sindex{2,100};

            //if we want to access data from the original array we need to
            //convert this to a 3D index
            itype oindex(3);
            s.index(sindex,oindex);

            //now the vector oindex holds the values {1,2,100} which can be used
            //to obtain data form the original array.

            \endcode
            The method assumes that all index containers are of appropriate
            size. If this is not the case an exception will be thrown

            \throws SizeMissmatchError if sindex does not match the rank of the
            selection or if oindex does not match the rank of the original array

            \tparam ITYPE container type for the indices
            \param sindex original index of the selection
            \param oindex new index with the rank of the original array
            */
            template<typename ITYPE> 
                void index(const ITYPE &sindex,ITYPE &oindex) const
            {
                //check size
                check_equal_size(_oshape,oindex,EXCEPTION_RECORD);
                check_equal_size(_shape,sindex,EXCEPTION_RECORD);

                typename ITYPE::iterator oiter = oindex.begin();
                typename ITYPE::const_iterator siter = sindex.begin();

                for(auto shape=_oshape.begin(), //iterator over original shape
                         offset=_offset.begin(),  //iterator over offset
                         stride=_stride.begin();  //iterator over stride
                    shape != _oshape.end();
                    ++shape,++offset,++stride)
                {
                    //add offset
                    *oiter = *offset;
                    if(*shape != 1)
                        *oiter += (*stride)*(*siter++);

                    ++oiter;
                }

            }

            //-----------------------------------------------------------------
            /*! 
            \brief compute the original index

            This is virtually the same as index(const ITYPE &sindex,const ITYPE
            &oindex) except that one does not have to take care about allocating
            the container for the original index.
            \tparam ITYPE container type (determined by the argument)
            \param sindex selection index
            \return instance of ITYPE with the index in the original array
            \sa template<typename ITYPE> index(const ITYPE &sindex,const ITYPE
            &oindex) const
            */
            template<typename ITYPE> ITYPE index(const ITYPE &sindex) const
            {
                ITYPE oindex(_oshape.size());
                try{ this->index(sindex,oindex); }
                EXCEPTION_FORWARD(SizeMissmatchError);

                return oindex;
            }
            //! output operator
            friend std::ostream &
                operator<<(std::ostream &o,const ArraySelection &s);
    };

            

//end of namespace
}
}

#endif
