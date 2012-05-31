#ifndef __NUMERICARRAY_HPP__
#define __NUMERICARRAY_HPP__

#include "Types.hpp"
#include "Shape.hpp"
#include "Iterator.hpp"

namespace pni{
namespace utils{

    template<typename T,typename STORAGE,typename ...> Array;


    template<typename T,typename STORAGE> class Array<T,STORAGE>
    {
        //need to do here a compiletime check if types are equal
        private:
            STORAGE _storage;
        public:
            //====================public types=================================
            typedef T value_type;
            typedef typename STORAGE::iterator iterator;
            typedef typename STORAGE::const_iterator const_iterator;
            
            //=====================public members==============================
            static const type_id = TypeIDMap<T>::type_id;

            //======================constructors and destructor================
            //! default constructor
            Array():_storage() {}

            //-----------------------------------------------------------------
            //! standard constructor
            Array(size_t n):_storage(n) {}

            //-----------------------------------------------------------------
            //! copy constructor
            Array(const Array<T,STORAGE> &a):_storage(a._storage) {}

            //-----------------------------------------------------------------
            //! move constructor
            Array(Array<T,STORAGE> &&a):_storage(std::move(a._storage)) {}

            //-----------------------------------------------------------------
            //! destructor
            ~Array() {} 

            //==================accessing data=================================
        
            T operator[](size_t i) const { return this->_storage[i]; }

            //-----------------------------------------------------------------
            T &operator[](size_t i) { return this->_storage[i]; }

            //-----------------------------------------------------------------
            T &operator()(size_t i) { return (*this)[i]; } 

            //-----------------------------------------------------------------
            T operator(size_t i) const { return (*this)[i]; }

            //-----------------------------------------------------------------
            Array<T,STORAGE>::iterator begin()
            {
                return this->_storage.begin();
            }

            //-----------------------------------------------------------------
            Array<T,STORAGE>::iterator end()
            {
                return this->_storage.end();
            }

            //-----------------------------------------------------------------
            Array<T,STORAGE>::const_iterator begin() const
            {
                return this->_storage.begin();
            }

            //-----------------------------------------------------------------
            Array<T,STORAGE>::const_iterator end() const
            {
                return this->_storage.end();
            }

            //=====================array inquery===============================
            size_t size() const { return this->_storage.size(); }

            Shape shape() const { return Shape({this->_size()}); }

    };


    template<typename T,typename STORAGE,typename INDEXMAP> 
        class Array<T,STORAGE,INDEXMAP>
    {
        private:
            STORAGE _storage;
            INDEXMAP _indexmap;
        public:
            //================public types=====================================
            typename T value_type;
            typename Iterator<Array<T,STORAGE,INDEXMAP>,0> iterator;
            typename Iterator<Array<T,STORAGE,INDEXMAP>,1> const_iterator;

            //===================public members================================
            static const TypeID type_id = TypeIDMap<T>::type_id;

            //===================constructors and destructors==================
            Array():_storage(),_indexmap() {}

            //-----------------------------------------------------------------
            template<typename ....ITypes> Array(ITypes ...indices):
                _storage(),
                _indexmap(indices...)
            {}

            //-----------------------------------------------------------------
            ~Array() {}

            //=====================array inquery===============================

            size_t size() const 
            { 
                return this->_indexmap.size(); 
            }

            //-----------------------------------------------------------------


            //=================================================================
            T operator[](size_t i) const
            {
                return this->_storage[i]; 
            }

            //-----------------------------------------------------------------
            T &operator[](size_t i) 
            { 
                return this->_storage[i]; 
            }

            //-----------------------------------------------------------------
            template<typename ...ITypes> T &operator()(ITypes ...indices)
            {
                return this->_storage[this->_indexmap.offset(indices...)];
            }

            //-----------------------------------------------------------------
            template<typename ...ITypes> T operator(ITypes ...indices) const
            {
                return this->_storage[this->_indexmap.offset(indices...)];
            }

    };

//end of namespace
}
}

#endif
