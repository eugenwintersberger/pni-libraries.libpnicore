#ifndef __FILELIST_HPP__
#define __FILELIST_HPP__

#include <iostream>
#include <list>
#include <boost/filesystem.hpp>
#include "../Types.hpp"

using namespace pni::utils;
using namespace boost::filesystem;


namespace pni{
namespace io{

    /*!
    \ingroup io_classes
    \brief file list generator

    This class can be used to manage list of files from several sources. 

    Strint template to represent a file range
    \code
    FileList("
    \endcode
    */ 
    class FileList
    {
        private:
            std::list<path> _list;
        public:
            //==================public types===================================
            typedef std::list<path>::iterator iterator;
            typedef std::list<path>::const_iterator const_iterator;

            //==================constructors and destructor=====================
            FileList():
                _list(0)
            {}

            //-----------------------------------------------------------------
            FileList(const std::String &tmpl);

            //-----------------------------------------------------------------
            FileList(const FileList &list):
                _list(list._list)
            {}

            //-----------------------------------------------------------------
            FileList(FileList &&list):
                _list(std::move(list._list))
            {}

            //=====================assignment operator==========================
            //! copy assignment operator
            FileList &operator=(const FileList &o)
            {
                if( this == &o) return *this;
                this->_list = o._list;
                return *this;
            }

            //------------------------------------------------------------------
            //! move assignment operator
            FileList &operator=(FileList &&o)
            {
                if( this == &o) return *this;
                this->_list = std::move(o._list);
                return *this;
            }

            //=====================iterator related methods=====================
            FileList::iterator begin() { return this->_list.begin(); }

            //------------------------------------------------------------------
            FileList::iterator end() { return this->_list.end(); }

            //------------------------------------------------------------------
            FileList::const_iterator begin() const 
            { 
                return this->_list.begin(); 
            }

            //------------------------------------------------------------------
            FileList::const_iterator end() const
            {
                return this->_list.end();
            }

    };
//end of namespace
}
}
#endif
