//definition of the abstract class DataValue - this is the 
//source of all other classes representing array or scalar data values
//This class basically manages units and description of a data value.

#ifndef __DATAVALUE_HPP__
#define __DATAVALUE_HPP__

#include<iostream>
#include<string>
#include<vector>

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
        const String &getUnit() { return _unit;}
        
        void setName(String value) { _name = value;}
        const String& getName() { return _name;}
        
        const String& getDescription() const { return _description; }
        void setDescription(const String &desc) { _description = desc; }
};

#endif
