#ifndef __STRIDETYPE__
#define __STRIDETYPE__

namespace pni{
namespace utils{


    //type holding the stride values
    template<size_t ...STRIDES> struct StrideHolder
    {
        static const size_t value[sizeof...(STRIDES)];
    };

    //fill values in
    template<size_t ...STRIDES> const size_t
        StrideHolder<STRIDES...>::value[sizeof...(STRIDES)] = {STRIDES...};

    //need a better stride computer

    /*!
    \brief class computing the stride for a particular type
    
    */
    /*
    template<size_t ...DIMS> class StrideComputer
    {
        private:
            template<size_t N,typename ...ETYPE> 
                static size_t _compute(size_t d,ETYPE ...dims)
            {
                return d*_compute(dims...);
            }

            static size_t _compute(size_t d)
            {
                return d;
            }
        public:
            template<size_t N> static size_t compute()
            {
                return _compute(DIMS...);    
            }

    };
    */

    template<size_t N,size_t CNT,bool DO,size_t ...DIMS> struct ComputeStride;

    template<size_t N,size_t CNT,size_t d,size_t ...DIMS> 
        struct ComputeStride<N,CNT,false,d,DIMS...>
    {
        static const size_t value = 1*ComputeStride<N,CNT+1,((CNT+1)>N),DIMS...>::value; 
    };

    template<size_t N,size_t CNT,size_t d,size_t ...DIMS> 
        struct ComputeStride<N,CNT,true,d,DIMS...>
    {
        static const size_t value = d*ComputeStride<N,CNT+1,((CNT+1)>N),DIMS...>::value;
    };

    //the break condition for the case that we want the stride for a dimension
    //being not the last dimension of the array
    template<size_t N,size_t CNT,size_t d> struct ComputeStride<N,CNT,true,d>
    {
        static const size_t value = d;
    };
   
    //this is the case for the break condition if we want the stride for the 
    //last dimension in the array. In this case CNT never reaches the condition
    //CNT+1>N because this would point to a location beyond the arrays bounds.
    template<size_t N,size_t CNT,size_t d> struct ComputeStride<N,CNT,false,d>
    {
        static const size_t value = 1;
    };

    /*
    template<size_t N,size_t CNT,size_t d,size_t ...DIMS> 
        struct ComputeStride<N,CNT,false,d,DIMS...>
    {
        static const size_t value = 1*ComputeStride<N,CNT+1,((CNT+1)>N),DIMS...>::value;
    };

    template<size_t N,size_t CNT> struct ComputeStride<N,CNT,false>
    {
        static const size_t value = 1;
    };*/
    
    template<size_t N,size_t ...DIMS> struct Stride
    {
        static const size_t value = ComputeStride<N,0,false,DIMS...>::value;
    };

    template<size_t ...DIMS> struct StrideCalc
    {
        template<size_t N> static constexpr size_t value()
        {
            return Stride<N,DIMS...>::value;
        }
    };




    //now we need to fill in the computed strides into the template parameter
    //list of the StrideHolder type - this gonna be tricky 

    //now we need some recursion to fill the stride holder
    template<typename SC,size_t CNT,size_t ...DIMS> struct create_stride_recursion
    {
        typedef typename create_stride_recursion<SC,CNT-1,SC::template value<CNT>(),DIMS...>::stride stride;
    };

    //break condition for the recursion
    template<typename SC,size_t ...DIMS> struct create_stride_recursion<SC,0,DIMS...>
    {
        typedef StrideHolder<SC::template value<0>(),DIMS...> stride;
    };

    //final type that creates the stride type
    template<size_t ...DIMS> struct create_stride
    {
        typedef typename create_stride_recursion<StrideCalc<DIMS...>,
                                                 sizeof...(DIMS)-2,
                                                 StrideCalc<DIMS...>::template value<sizeof...(DIMS)-1>()>::stride stride;
    };

//end of namespace
}
}
#endif
