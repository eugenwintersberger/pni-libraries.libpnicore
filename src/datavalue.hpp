//definition of the abstract class DataValue - this is the 
//source of all other classes representing array or scalar data values
//This class basically manages units and description of a data value.

#ifndef __DATAVALUE_HPP__
#define __DATAVALUE_HPP__

#include<iostream>
#include<string>
#include<vector>

#include "buffer.hpp"
#include "types.hpp"


#define DEFAULT_VALUE_DESCRIPTION String("none")
#define DEFAULT_VALUE_NAME String("none")
#define DEFAULT_VALUE_UNIT String("(a.u.)")

//! base class for all data quantities in memory

//! Class DataValue is the base class of all representations of
//! data objects in memory.

class DataValue{
    protected:
        String _unit;         //!< string with the unit of the data value
        String _description;  //!< description of the data value
        String _name;         //!< name of the data value (name in the file)
                              //!< must not conform to the mnemonic of the instantiated
        					  //!< object in memory
    public:
        DataValue(); //default constructor
        DataValue(const DataValue &); //copy constructor
        DataValue(const String &);
        DataValue(const String &,const String &);
        DataValue(const String &,const String &,const String &);
        virtual ~DataValue(){}  //destructor - default
        
        void setUnit(String value) { _unit = value;}
        void setUnit(const char *v) { _unit = String(v);}
        const String &getUnit() const { return _unit;}
        
        void setName(String value) { _name = value;}
        void setName(const char *v) { _name = String(v);}
        const String& getName() const { return _name;}
        
        const String& getDescription() const { return _description; }
        void setDescription(const String &desc) { _description = desc; }
        void setDescription(const char *v) { _description = String(v);}

        virtual AbstractBuffer *getBuffer() { return NULL;}

        friend std::ostream &operator<<(std::ostream &o,const DataValue &v);
};

#endif
