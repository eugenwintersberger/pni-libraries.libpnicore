//a static allocator for a vector class

#include <type_traits>
#include <new>


namespace pni{
namespace core{

    /*
    \brief a static allocator

    This allocator is used for static buffers in std::vector. Memory is
    allocated statically.
    Unlike the original (pre C++11) standard allocator this allocator holds a
    state. This is necessary as otherwise we would need to allocate memory at
    runtime (which we do not want).

    \tparam T data type 
    \tparam N number of elements to allocate
    */
    template<typename T,size_t N> class static_allocator
    {
        public:
            //! the element type
            typedef T value_type;
            //! the pointer type
            typedef T* pointer;
            //! the reference type
            typedef T& reference;
            //! a constant pointer type
            typedef const T* const_pointer;
            //! constant reference type
            typedef const T& const_reference;
            //! the size type
            typedef size_t size_type;

            //! as the allocator holds a state it most be propagated when the
            //container is moved
            typedef std::true_type propagate_on_move_assignment;

            template<typename U> struct rebind
            {
                typedef static_allocator<U,N> other;
            };

        private:
            T _data[N]; //!< storage
        public:

            //-----------------------------------------------------------------
            /*!
            \brief allocate memory

            
            \throws std::bad_alloc if n does not match N
            \param n number of element to allocate
            \return pointer to the allocated memory
            */
            pointer allocate(size_type n)
            {
                if(N!=n) throw std::bad_alloc();

                return _data;
            }

            //-----------------------------------------------------------------
            /*!
            \brief deallocate memory

            This method should deallocate memory. However, it has nothing to do
            with statically allocated memory.

            \param p pointer to memory
            \param n number of elements allocated for p
            */
            void deallocate(pointer p,size_type n) { }

            //-----------------------------------------------------------------
            //! return the maximum size
            size_type max_size() const { return N; }

            
    };

    /*!
    \brief equality operator

    This operator returns true by default. 
    */
    template<typename T,size_t N>
    bool operator==(const static_allocator<T,N> &a1,
                    const static_allocator<T,N> &a2)
    {
        return true;
    }

    /*!
    \brief inequality check

    */
    template<typename T,size_t N>
    bool operator!=(const static_allocator<T,N> &a1,
                    const static_allocator<T,N> &a2)
    {
        return false;
    }

//end of namespace
}
}
