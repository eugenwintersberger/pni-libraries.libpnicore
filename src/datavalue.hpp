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

//default values for name, unit, and description of a DataValue
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
        //! default constructor
        DataValue();
        //! copy constructor
        DataValue(const DataValue &);
        //! constructor

        //! \param  n name of the data value
        DataValue(const String &n);
        //! constructor

        //! \param n name of the data value
        //! \param u unit of the data value
        DataValue(const String &n,const String &u);
        //! constructor

        //! \param n name of the data value
        //! \param u unit of the data value
        //! \param d description of the data value
        DataValue(const String &n,const String &u,const String &d);
        //! destructor
        virtual ~DataValue(){}
        
        //! set the unit of the data value

        //! \param value the unit as a string object
        void setUnit(const String &value) { _unit = value;}
        //! se the unit of the data value

        //! \param v the unit as a char array
        void setUnit(const char *v) { _unit = String(v);}
        //! get the unit of the data value

        //! \return const reference to the unit string
        const String &getUnit() const { return _unit;}
        
        //! set the name of the data value

        //! \param n data value name as string
        void setName(const String &n) { _name = n;}

        //! set the name of the data value

        //! \param v name as a char array
        void setName(const char *v) { _name = String(v);}
        //! get the name of the data value

        //! \return the name of the objet as a reference to a string
        const String& getName() const { return _name;}
        
        //! get the description of the object

        //! \return object description as a string reference
        const String& getDescription() const { return _description; }
        //! set the description

        //! \param desc reference to the description string
        void setDescription(const String &desc) { _description = desc; }
        void setDescription(const char *v) { _description = String(v);}

        //return an abstract buffer - this is not very good design
        //need to do this in a better way (how to handle buffers)
        virtual AbstractBuffer *getBuffer() { return NULL;}

        friend std::ostream &operator<<(std::ostream &o,const DataValue &v);
};

#endif
