/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Implementation of class TIFFIFDEntry
 *
 * Created on: Apr 24, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */



#include "../../Exceptions.hpp"
#include "IFDEntry.hpp"
#include "Standard.hpp"


namespace pni{
namespace io{
namespace tiff{

    //map object associating TIFF type tags to IDFEntryTypeId enums
    std::map<UInt16,IFDEntryTypeID> 
        TypeTag2EntryTypeId = {{1,IFDEntryTypeID::BYTE},
                               {2,IFDEntryTypeID::ASCII},
                               {3,IFDEntryTypeID::SHORT},
                               {4,IFDEntryTypeID::LONG},
                               {5,IFDEntryTypeID::RATIONAL},
                               {6,IFDEntryTypeID::SBYTE},
                               {7,IFDEntryTypeID::UNDEFINED},
                               {8,IFDEntryTypeID::SSHORT},
                               {9,IFDEntryTypeID::SLONG},
                               {10,IFDEntryTypeID::SRATIONAL},
                               {11,IFDEntryTypeID::FLOAT},
                               {12,IFDEntryTypeID::DOUBLE}};

    //map object associating IDFEntryTypeIds to PNI TypeIDs
    std::map<IFDEntryTypeID,TypeID> 
        EntryTypeId2TypeID = {{IFDEntryTypeID::BYTE,TypeID::UINT8},
                              {IFDEntryTypeID::ASCII,TypeID::STRING},
                              {IFDEntryTypeID::SHORT,TypeID::UINT16},
                              {IFDEntryTypeID::LONG,TypeID::UINT32},
                              {IFDEntryTypeID::RATIONAL,TypeID::FLOAT64},
                              {IFDEntryTypeID::SBYTE,TypeID::INT8},
                              {IFDEntryTypeID::UNDEFINED,TypeID::NONE},
                              {IFDEntryTypeID::SSHORT,TypeID::INT16},
                              {IFDEntryTypeID::SLONG,TypeID::INT32},
                              {IFDEntryTypeID::SRATIONAL,TypeID::FLOAT64},
                              {IFDEntryTypeID::FLOAT,TypeID::FLOAT32},
                              {IFDEntryTypeID::DOUBLE,TypeID::FLOAT64}};


    //==================constructors and destructor========================
    //implementation of the  default constructor
    IFDEntry::IFDEntry():
        _tag(0),
        _tid(IFDEntryTypeID::UNDEFINED),
        _size(0),
        _data(0)
    {}

    //---------------------------------------------------------------------
    //implementation of the copy constructor
    IFDEntry::IFDEntry(const IFDEntry &e):
        _tag(e._tag),
        _tid(e._tid),
        _size(e._size),
        _data(e._data)
    {}

    //---------------------------------------------------------------------
    //implementation of the  move constructor
    IFDEntry::IFDEntry(IFDEntry &&e):
        _tag(std::move(e._tag)),
        _tid(std::move(e._tid)),
        _size(std::move(e._size)),
        _data(std::move(e._data))
    {}

    //---------------------------------------------------------------------
    //implementation of the standard constructor
    IFDEntry::IFDEntry(UInt16 tag,IFDEntryTypeID tid,size_t size, 
                      std::streampos data):
        _tag(tag),
        _tid(tid),
        _size(size),
        _data(data)
    { }

    //---------------------------------------------------------------------
    //implementation of the destructor
    IFDEntry::~IFDEntry()
    {}

    //=====================assignment operators============================
    //implementation of the copy assignment operator
    IFDEntry &IFDEntry::operator=(const IFDEntry &e)
    {
        if(this == &e) return *this;
        
        _tag = e._tag;
        _tid = e._tid;
        _size = e._size;
        _data = e._data;
        return *this;
    }

    //---------------------------------------------------------------------
    //implementation of the move assignment operator
    IFDEntry &IFDEntry::operator=(IFDEntry &&e)
    {
        if(this == &e) return *this;
        _tag = std::move(e._tag);
        _tid = std::move(e._tid);
        _size = std::move(e._size);
        _data = std::move(e._data);
        return *this;
    }

    //===========implementation of static methods==========================
    IFDEntry IFDEntry::create_from_stream(std::ifstream &stream)
    {
        UInt16 tag = 0;
        stream.read((char *)(&tag),2);
        
        UInt16 tid = 0;
        stream.read((char *)(&tid),2);

        UInt32 count = 0;
        stream.read((char *)(&count),4);

        IFDEntry e(tag,TypeTag2EntryTypeId[tid],count,stream.tellg());
        //add additional for byte 
        stream.seekg(4,std::ios::cur);
        return e;
    
    }

    //=======================class methods=================================
    //implementation of nelements
    size_t IFDEntry::size() const
    {
        return _size;
    }

    //----------------------------------------------------------------------
    String IFDEntry::name() const
    {
       try{
           return TIFFTagNameMap[_tag];
       }catch(...){
           return String("unknown");
       }
    }

    //-----------------------------------------------------------------------
    TypeID IFDEntry::type_id() const
    {
        return EntryTypeId2TypeID[_tid];
    }

    //-----------------------------------------------------------------------
    void IFDEntry::_read_entry_data(std::vector<String> &r,std::ifstream &stream)
    {
        EXCEPTION_SETUP("void IFDEntry::_read_entry_data(std::vector<String> "
                "&r,std::ifstream &stream)");

        //now we have to walk through all types available in TIFF - not very
        //nice but we have no other choice at runtime
        if(this->_tid == IFDEntryTypeID::ASCII)
            IFDEntryReader<String,String>::read(r,stream);
        else
        {
            //reset stream position
            EXCEPTION_INIT(TypeError,"IFD entry is of unknown or "
                    "incompatible type!");
            EXCEPTION_THROW();
        }
       
    }

    //=================implementation of friend methods and operators========
    std::ostream &operator<<(std::ostream &o,const IFDEntry &e)
    {
        o<<"IFD entry: "<<e.name()<<" (tag="<< e._tag<<") with "<<e.size()<<" of type ";
        o<<e.type_id();
        return o;
    }

//end of namespace
}
}
}
