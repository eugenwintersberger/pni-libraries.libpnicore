#ifndef __ARRAYSELECTION_HPP__
#define __ARRAYSELECTION_HPP__

#include <vector>
#include <algorithm>

#include "ExceptionUtils.hpp"
#include "Slice.hpp"

namespace pni{
namespace utils{

    /*! 
    \ingroup multidim_array_classes
    \brief select data form a multidimensional array

    This type used to select data from a multidimensional array. Its primary
    purpose is to compute new indices that fit to the original array from the
    indices to the selection. 
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
            //! compute original index
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
            //! compute the original index
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
