#ifndef __ABSTRACTBUFFER_HPP__
#define __ABSTRACTBUFFER_HPP__

#include "Types.hpp"

namespace pni{
namespace utils{

    class AbstractBuffer
    {
        public:
            //=================constructors and destructor=====================
            //! default constructor
            AbstractBuffer();

            //-----------------------------------------------------------------
            //! copy constructor
            AbstractBuffer(const AbstractBuffer &buffer);

            //-----------------------------------------------------------------
            //! move constructor
            AbstractBuffer(AbstractBuffer &&buffer);

            //-----------------------------------------------------------------
            //! destructor
            virtual ~AbstractBuffer();

            //===============assignment operators==============================
            //! copy assigment operator
            AbstractBuffer &operator=(const AbstractBuffer &buffer);

            //-----------------------------------------------------------------
            //! move assignment operator
            AbstractBuffer &operator=(AbstractBuffer &&buffer);

            //=================public member functions=========================
            virtual size_t size() const = 0;
            virtual const void *ptr() const = 0;
            virtual TypeID type_id() const = 0;

    };

}
}

#endif
