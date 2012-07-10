
#include "SizeType.hpp"
#include "StrideType.hpp"
namespace pni{
namespace utils{

    template<size_t D,bool ITERATE,size_t ...DIMS> struct IndexCreator
    {
        template<typename CTYPE> static void index(size_t offset,CTYPE &c)
        {
                size_t t = offset%StrideCalc<DIMS...>::template value<D>();
                c[D] = (offset-t)/StrideCalc<DIMS...>::template value<D>();
                IndexCreator<D+1,((D+1)<((sizeof ...(DIMS))-1)),DIMS...>::template
                    index(t,c);
        }
    };

    template<size_t D,size_t ...DIMS> struct IndexCreator<D,false,DIMS...>
    {
        template<typename CTYPE> static void index(size_t offset,CTYPE &c)
        {
                size_t t = offset%StrideCalc<DIMS...>::template value<D>();
                c[D] = (offset-t)/StrideCalc<DIMS...>::template value<D>();
        }
    };

    template<size_t D,bool FINISHED,size_t ...DIMS> struct OffsetCalc
    {
        template<typename CTYPE> static size_t offset(const CTYPE &c)
        {
            std::cout<<"iteration : "<<D<<" index = "<<c[D]<<" stride = "<<StrideCalc<DIMS...>::template value<D>()<<std::endl;
            return StrideCalc<DIMS...>::template value<D>()*c[D]+
                   OffsetCalc<D+1,((D+1)>=(sizeof...(DIMS))),DIMS...>::offset(c);
        }
    };

    template<size_t D,size_t ...DIMS> struct OffsetCalc<D,true,DIMS...>
    {
        template<typename CTYPE> static size_t offset(const CTYPE &c)
        {
           return 0;
        }
    };




    /*!
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
    */
    template<size_t ...DIMS> class StaticShape
    {
        private:
            static const size_t _dims[sizeof ...(DIMS)];  // static buffer holding the data

            //==============private member functions===========================
            template<size_t d,typename ...ITYPES> 
            size_t _offset(size_t i1,ITYPES ...indices) const
            {
                
                return StrideCalc<DIMS...>::template value<d>()*i1+
                       _offset<d+1>(indices...);
            }

            //-----------------------------------------------------------------
            template<size_t d> size_t _offset(size_t i) const 
            { 
                return StrideCalc<DIMS...>::template value<d>()*i; 
            }



        public:
            //! default constructor
            StaticShape() { }
            
            //-----------------------------------------------------------------

            size_t rank() const { return sizeof...(DIMS); }

            //-----------------------------------------------------------------
            size_t size() const { return SizeType<DIMS...>::size;}

            //-----------------------------------------------------------------
            template<typename CONTAINER> CONTAINER shape() const
            {
                CONTAINER c(this->rank());

                size_t index = 0;
                for(typename CONTAINER::value_type &v: c)
                    v = this->dim[index];

                return c;
            }

            //-----------------------------------------------------------------
            template<typename ...ITYPES >
                size_t offset(size_t i1,ITYPES ...indices) const
            {
                static_assert((sizeof...(DIMS)) == (sizeof...(indices)+1),
                              "Number of indices does not match shape rank!");

                return StrideCalc<DIMS...>::template value<0>()*i1+
                       _offset<1>(indices...);
            }

            //-----------------------------------------------------------------
            template<typename CTYPE> size_t offset(const CTYPE &c) const
            {
                if(c.size() != this->rank())
                {
                    //throw an exception here
                }
                
                return OffsetCalc<0,false,DIMS...>::offset(c);
            }


            //-----------------------------------------------------------------
            template<typename CTYPE> void index(size_t offset,CTYPE &c) const
            {
                if(c.size() != this->rank())
                {
                    //throw an exception here
                }

                IndexCreator<0,true,DIMS...>::index(offset,c);
            }

            //-----------------------------------------------------------------
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
