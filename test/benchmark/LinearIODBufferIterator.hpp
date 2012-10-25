#ifndef __LINEARIODBUFFERITERATOR_HPP__
#define __LINEARIODBUFFERITERATOR_HPP__

template<typename BUFFERT> class LinearIODBufferIterator
{
    private:
        BUFFERT _buffer;
        typename BUFFERT::value_type _result;
    public:
        //==================construtors========================================
        LinearIODBufferIterator(size_t size):_buffer(size) {}

        //================public member functions==============================
        void write_data()
        {
            typedef typename BUFFERT::value_type value_t;
            value_t index(0);

            for(auto iter = _buffer.begin();iter!=_buffer.end();++iter) 
                *iter = index++;
        }

        //---------------------------------------------------------------------
        void read_data()
        {
            _result = typename BUFFERT::value_type(0);

            for(auto iter = _buffer.begin();iter!=_buffer.end();++iter) 
                _result += *iter;
        }
            
};

#endif
