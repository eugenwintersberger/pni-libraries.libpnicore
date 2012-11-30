#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include "AbstractBuffer.hpp"
#include "BufferHolder.hpp"

namespace pni{
namespace utils{

    /*!
    \brief type erasure for buffers

    This class is a type erasure for buffer types. It can be used to access
    basic methods of the various buffer types provided by libpniutils. 
    */
    class Buffer
    {
        private:
            AbstractBuffer *_ptr; //! pointer to an abstract buffer
        public:
            //======================constructor and destructor=================
            //! default constructor
            Buffer():_ptr(nullptr) {}
            
            //-----------------------------------------------------------------
            //! move constructor
            Buffer(Buffer &&buffer);

            //-----------------------------------------------------------------
            //! copy constructor
            Buffer(const Buffer &buffer);

            //-----------------------------------------------------------------
            /*! 
            \brief constructor 

            This constructors creates a copy of an instance of the buffer type
            BTYPE. 
            \tparam BTYPE buffer type
            \param buffer const. reference to an instance of BTYPE
            */
            template<typename BTYPE> explicit Buffer(const BTYPE &buffer):
                _ptr(new BufferHolder<BTYPE>(buffer))
            {}

            //-----------------------------------------------------------------
            /*!
            \brief constructor

            Move constructor for the buffer type erasure from an instance of the
            buffer type BTYPE. 
            \tparam BTYPE buffer type
            \param buffer rvalue reference to an instance of BTYPE
            */
            template<typename BTYPE> explicit Buffer(BTYPE &&buffer):
                _ptr(new BufferHolder<BTYPE>(std::move(buffer)))
            {}
            

            //=====================assignment operators========================
            //! copy assignment
            Buffer &operator=(const Buffer &buffer);

            //-----------------------------------------------------------------
            //! move constructor
            Buffer &operator=(Buffer &&buffer);

            //-----------------------------------------------------------------
            /*!
            \brief copy conversion assignment
            */
            template<typename BTYPE> Buffer &operator=(const BTYPE &buffer)
            {
                if(this == &buffer) return *this;

                if(_ptr) delete _ptr;

                _ptr = new BufferHolder<BTYPE>(buffer);

                return *this;
            }

            //-----------------------------------------------------------------
            template<typename BTYPE> Buffer &operator=(BTYPE &&buffer)
            {
                if(this == &buffer) return *this;

                if(_ptr) delete _ptr;

                _ptr = new BufferHolder<BTYPE>(std::move(buffer));

                return *this;
            }

            //====================public member functions======================
            size_t size() const;

            const void *ptr() const;

            TypeID type_id() const;
    };



//end of namespace
}
}

#endif
