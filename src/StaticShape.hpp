
#include "SizeType.hpp"
namespace pni{
namespace utils{

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
            size_t _dimstrides[sizeof...(DIMS)]; //!< array holding dimension strides

            //==============private member functions===========================
            template<typename ...ITYPES>
            size_t _offset(size_t d,size_t i1,ITYPES ...indices)
            {
                
                return _dimstrides[d]::size*i1+_offset(d+1,indices...);
            }

            //-----------------------------------------------------------------
            size_t _offset(size_t d) { return 0; }

            //-----------------------------------------------------------------
            template<typename ...ITYPES>
            void _compute_dimstrides(size_t d,size_t i1,ITYPES ...DIMS)
            {
                _dimstrides[d] = SizeType<DIMS...>::size;
                _compute_dimstrides(d+1,DIMS...);
            }

            //-----------------------------------------------------------------
            void _compute_dimstrides(size_t d)
            {
                //do nothing here - just break the recursion.
            }

        public:
            
            //-----------------------------------------------------------------

            size_t rank() const { return sizeof...(DIMS); }

            //-----------------------------------------------------------------
            size_t size() const { return SizeType<DIMS...>::size;}

            //-----------------------------------------------------------------
            template<typename ...ITYPES 
                size_t offset(size_t i1,ITYPES ...indices) const
            {
                static_assert(assert(sizeof...(DIMS) == sizeof...(indices),
                              "Number of indices does not match shape rank!");

                return _dimstrides[0]*i1+_offset(1,indices...);
            }

            //-----------------------------------------------------------------
            template<typename CTYPE> size_t offset(const CTYPE &c) const
            {
                if(c.size() != this->rank())
                {
                    //throw an exception here
                }

            }

            //-----------------------------------------------------------------
            template<typename CTYPE> void index(size_t o,CTYPE &c) const
            {
                if(c.size() != this->rank())
                {
                    //throw an exception here
                }

                size_t o,t;
                o = offset;
                for(size_t d = 0;d<this->rank();d++)
                {
                    t = o%this->_dimstrides[d];
                    c[d] = (o-t)/this->_dimstrides[d];
                    o = t;
                }
            }

            //-----------------------------------------------------------------
            template<typename CTYPE> CTYPE index(size_t o) const
            {
                CTYPE c(this->rank());

                this->index(o,c);
                return c;
            }

    };

//end of namespace
}
}
