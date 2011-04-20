//definition of the abstract class DataValue - this is the 
//source of all other classes representing array or scalar data values
//This class basically manages units and description of a data value.

#ifndef __DATAVALUE_HPP__
#define __DATAVALUE_HPP__

#include<iostream>
#include<string>
#include<vector>

#include "buffer.hpp"

typedef std::string String;

#define DEFAULT_VALUE_DESCRIPTION String("none")
#define DEFAULT_VALUE_NAME String("none")
#define DEFAULT_VALUE_UNIT String("(a.u.)")


class DataValue{
    protected:
        String _unit;
        String _description;
        String _name;
    public:
        DataValue(); //default constructor
        DataValue(const DataValue &); //copy constructor
        DataValue(const String &);
        DataValue(const String &,const String &);
        DataValue(const String &,const String &,const String &);
        virtual ~DataValue(){}  //destructor - default
        
        void setUnit(String value) { _unit = value;}
        void setUnit(const char *v) { _unit = std::string(v);}
        const String &getUnit() const { return _unit;}
        
        void setName(String value) { _name = value;}
        void setName(const char *v) { _name = std::string(v);}
        const String& getName() const { return _name;}
        
        const String& getDescription() const { return _description; }
        void setDescription(const String &desc) { _description = desc; }
        void setDescription(const char *v) { _description = std::string(v);}

        virtual AbstractBuffer *getBuffer() { return NULL;}

        friend std::ostream &operator<<(std::ostream &o,const DataValue &v);
};

#endif
