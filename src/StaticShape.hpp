
#include <iostream>
#include <sstream>

#include "SizeType.hpp"
#include "StrideType.hpp"
#include "Exceptions.hpp"
#include "ExceptionUtils.hpp"

namespace pni{
namespace utils{

    //=========================================================================
    /*! 
    \ingroup util_classes
    \brief create index container

    Type for computing the indices belonging to a particular offset and returns
    the index in a container. It must be ensured that the container is of
    sufficient size. The class provides a static function template which is
    called recursively to do the job. A specialized version of the type exists
    implementing the break condition.
    \tparam D index counter
    \tparam ITERATE decide if continue iteration
    \tparam DIMS elements along each dimensin
    */
    template<size_t D,bool ITERATE,size_t ...DIMS> struct IndexCreator
    {
        /*!
        \brief compute index

        \tparam CTYPE container type
        \param offset linear offset for which the index should be calculated
        \param c container type where to store indices
        */
        template<typename CTYPE> 
            static void index(size_t offset,typename CTYPE::iterator c)
        {
                size_t t = offset%StrideCalc<DIMS...>::template value<D>();
                *c = (offset-t)/StrideCalc<DIMS...>::template value<D>();
                IndexCreator<D+1,((D+1)<((sizeof ...(DIMS))-1)),DIMS...>::template
                    index<CTYPE>(t,++c);
        }
    };

    //=========================================================================
    /*! 
    \ingroup util_classes
    \brief specialization of IndexCreator

    This specialization of IndexCreator acts as a break condition. The ITERATE
    template parameter is set to false for this type.
    \tparam D dimension counter
    \tparam DIMS elements along each dimension
    */
    template<size_t D,size_t ...DIMS> struct IndexCreator<D,false,DIMS...>
    {
        /*!
        \brief add last index to container

        Add the last index to the container. 
        \tparam CTYPE container type
        \param offset linear offset for which the index should be calculated
        \param c container type where to store the indices
        */
        template<typename CTYPE> 
            static void index(size_t offset,typename CTYPE::iterator c)
        {
                size_t t = offset%StrideCalc<DIMS...>::template value<D>();
                *c = (offset-t)/StrideCalc<DIMS...>::template value<D>();
        }
    };

    //=========================================================================
    /*! 
    \ingroup util_classes
    \brief type computing offset

    Type can be used to compute the offset from indices stored in a container
    type. The class provides a static template method doing the job. 
    \tparam D index counter
    \tparam FINISHED set to true of the calculation is finished
    \tparam DIMS elements along each dimension
    */
    template<size_t D,bool FINISHED,size_t ...DIMS> struct OffsetCalc
    {
        /*!
        \brief compute offset

        */
        template<typename CTYPE> 
            static size_t offset(typename CTYPE::const_iterator c)
        {
            return StrideCalc<DIMS...>::template value<D>()*(*c)+
                   OffsetCalc<D+1,((D+1)>=(sizeof...(DIMS))),DIMS...>::
                   template offset<CTYPE>(++c);
        }
    };

    //=========================================================================
    /*! 
    \ingroup util_classes
    \brief specialized version of OffsetCalc

    */
    template<size_t D,size_t ...DIMS> struct OffsetCalc<D,true,DIMS...>
    {
        /*! 
        \brief compute offset

        Final version of the offset computation. Ends the template recursion.
        \tparam CTYPE container type where to store the index
        \param c container where to store the data
        \return offset value
        */
        template<typename CTYPE> 
            static size_t offset(typename CTYPE::const_iterator c)
        {
           return 0;
        }
    };


    //=========================================================================
    /*!
    \ingroup util_classes
    \brief static array shape type

    This type can be used to represent a static array shape. The shape object is
    entirely determined at compile time by its template parameters. 
    For instance, the following code creates a static shape of size 4x10
    \code
    StaticShape<4,10> shape;
    \endcode
    As this type cannot be configured at runtime it is perfectly suited for
    static the creation of n-dimensional static array types like matrices or
    vectors. 
    \tparam DIMS number of elements along each dimension
    */
    template<size_t ...DIMS> class StaticShape
    {
        private:
            //! static buffer holding the data
            static const size_t _dims[sizeof ...(DIMS)];  

            //==============private member functions===========================
            /*! 
            \brief compute offset 

            Computes the memory offset to a multidimensional index which is
            passed by the user as a variadic template. This private method is
            called recursively until a break condition is reached.
            \throws IndexError if i1 exceeds the number of elements along
            dimension d
            \tparam d dimension counter
            \tparam ITYPES index types
            \param i1 actual index whose contribute to the offset is computed
            \param indices the residual indices in the variadic argument list
            \return memory offset
            */
            template<size_t d,typename ...ITYPES> 
            size_t _offset(size_t i1,ITYPES ...indices) const
            {
                check_index(i1,_dims[d],
                        "template<size_t d,typename ...ITYPES> size_t "
                        "_offset(size_t i1,ITYPES ...indices) const");
                
                return StrideCalc<DIMS...>::template value<d>()*i1+
                       _offset<d+1>(indices...);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief compute offset - break condition

            The break condition for the recursive offset computation from an
            index passed as a variadic argument list.
            \throws IndexError if i exceeds the number of elements along
            dimension d
            \tparam d index counter
            \param i the last index to process
            \return offset value
            */
            template<size_t d> size_t _offset(size_t i) const 
            { 
                check_index(i,this->_dims[d],
                        "template<size_t d> size_t _offset(size_t i) const");

                return StrideCalc<DIMS...>::template value<d>()*i; 
            }

        public:
            //! default constructor
            StaticShape() { }
            
            //-----------------------------------------------------------------
            /*! 
            \brief get number of dimensions

            Return the number of dimensions of the shape object.
            \return number of dimensions
            */
            size_t rank() const { return sizeof...(DIMS); }

            //-----------------------------------------------------------------
            /*! 
            \brief get number of elements

            Return the total number of elements described by the shape object.
            \return number of elements
            */
            size_t size() const { return SizeType<DIMS...>::size;}

            //-----------------------------------------------------------------
            /*! 
            \brief get shape

            Return the number of elements along each dimension in a container 
            specified by the user. The container can be each STL or other type
            that conforms to the STL forward iterator interface. 
            This example shows how to use this 
            \code
            StaticShape<3,4,5,2> s;
            auto s.shape<std::vector<size_t> >();
            \endcode

            \tparam CONTAINER  container type
            \return container with elements along each dimension
            */
            template<typename CONTAINER> CONTAINER shape() const
            {
                CONTAINER c(this->rank());

                size_t index = 0;
                for(typename CONTAINER::value_type &v: c)
                    v = this->_dims[index];

                return c;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief compute offset

            Compute an offset from a multidimensional index passed as a variadic
            argument list. This method is quite comfortable as this example
            shows
            \code
            StaticShape<3,4,5> s;

            size_t offset = s.offset(1,2,3);
            \endcode
            The method produces a compile time error if the number of indices
            does not match the rank of the shape.

            \throws IndexError if one of the indices exceeds the number of
            elements along its corresponding dimension
            \tparam ITYPES index types
            \param indices the indices along each dimension
            \return offset value
            */
            template<typename ...ITYPES >
                size_t offset(size_t i1,ITYPES ...indices) const
            {
                //in cases where the number of arguments do not match the rank
                //of the shape this will throw a compile time error
                static_assert((sizeof...(DIMS)) == (sizeof...(indices)+1),
                              "Number of indices does not match shape rank!");

                //check the index for the first dimension
                check_index(i1,this->_dims[0],
                        "template<typename ...ITYPES > size_t "
                        "offset(size_t i1,ITYPES ...indices) const");

                return StrideCalc<DIMS...>::template value<0>()*i1+
                       _offset<1>(indices...);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief return offset 

            Return the offset of a multidimensional index pass to the function
            as a container. If the size of the index container is not equal to
            the rank of the shape object a ShapeMissmatchError is thrown.
            \code
            StaticShape<3,4,5> s;
            std::vector<size_t> index{1,2,3};
            size_t offset = s.offset(index);
            \endcode
            \throws ShapeMissmatchError if rank and container size do not match
            \throws IndexError if one of the indices exceeds the number of
            elements along its dimensions
            \param c container with indices
            \return offset value
            */
            template<typename CTYPE> size_t offset(const CTYPE &c) const
            {
                if(c.size() != this->rank())
                {
                    ShapeMissmatchError e;
                    std::stringstream ss;
                    ss<<"Size of container ("<<c.size()<<") does not match";
                    ss<<" rank ("<<this->rank()<<")!";
                    e.description(ss.str());
                    e.issuer("template<typename CTYPE> size_t offset"
                             "(const CTYPE &c) const");
                    throw e;
                }

                size_t index = 0;
                for(auto i: c)
                {
                    if(i>=this->_dims[index++])
                    {
                        std::stringstream ss;
                        ss<<"Index "<<--index<<" is "<<i;
                        ss<<" and exceeds its maximum value";
                        ss<<"of "<<this->_dims[--index]<<"!";
                        IndexError error;
                        error.issuer("template<typename CTYPE> size_t "
                                     "offset(const CTYPE &c) const");
                        error.description(ss.str());
                        throw error;
                    }
                }
                
                return OffsetCalc<0,false,DIMS...>::template offset<CTYPE>(c.begin());
            }

            //-----------------------------------------------------------------
            /*! 
            \brief compute the index

            Compute the index belonging to a particular linear memory offset.
            The targeting container is passed as the second argument of the
            method. It is assumed that the size of the container matches the
            rank of the shape.
            \throws ShapeMissmatchError if container size and shape rank do not
            match
            \throws SizeMissmatchError if offset exceeds the total size of the
            shape
            \param offset linear offset 
            \param c target container
            */
            template<typename CTYPE> void index(size_t offset,CTYPE &c) const
            {
                if(c.size() != this->rank())
                {
                    ShapeMissmatchError e;
                    std::stringstream ss;
                    ss<<"Size of container ("<<c.size()<<") does not match";
                    ss<<" rank ("<<this->rank()<<")!";
                    e.description(ss.str());
                    e.issuer("template<typename CTYPE> void index(size_t "
                             "offset,CTYPE &c) const");
                    throw e;
                }

                if(offset >= this->size())
                {
                    std::stringstream ss;
                    ss<<"Offset "<<offset<<" exceeds shape size ";
                    ss<<this->size()<<"!";

                    SizeMissmatchError error;
                    error.issuer("template<typename CTYPE> void "
                                 "index(size_t offset,CTYPE &c) const");
                    error.description(ss.str());
                    throw error;
                }

                IndexCreator<0,true,DIMS...>::template index<CTYPE>(offset,c.begin());
            }

            //-----------------------------------------------------------------
            /*! 
            \brief compute the index from an offset

            Compute the index from an offset and return it in a container. 
            \throws SizeMissmatchError if o exceeds the size of the shape
            \tparam CTYPE container type
            \param o offset value 
            \return the container with the indices
            */
            template<typename CTYPE> CTYPE index(size_t o) const
            {
                CTYPE c(this->rank());

                this->index(o,c);
                return c;
            }

    };

    //ensure that the dimension data is loaded into the buffer
    template<size_t ...DIMS> 
        const size_t StaticShape<DIMS...>::_dims[sizeof...(DIMS)] = {DIMS...};

//end of namespace
}
}
