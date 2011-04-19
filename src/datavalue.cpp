//implementation of the DataValue class

#include<iostream>
#include<string>

#include "datavalue.hpp"

//implementation of the default constructor
DataValue::DataValue(){
    _name = DEFAULT_VALUE_NAME;
    _description = DEFAULT_VALUE_DESCRIPTION;
    _unit = DEFAULT_VALUE_UNIT;
}

//implementation of the copy constructor
DataValue::DataValue(const DataValue &value){
    _name = value._name;
    _unit = value._unit;
    _description = value._description;
}

//implementation of a constructor setting only the name
DataValue::DataValue(const String &n){
    _name = n;
    _description = DEFAULT_VALUE_DESCRIPTION;
    _unit = DEFAULT_VALUE_UNIT;
}

//implementation of a constructor setting name and unit
DataValue::DataValue(const String &n,const String &u){
    _name = n;
    _unit = u;
    _description = DEFAULT_VALUE_DESCRIPTION;
}

//implementation of a constructor setting name,unit, and description
DataValue::DataValue(const String &n,const String &u,const String &d){
    _name = n;
    _unit = u;
    _description = d;
}
