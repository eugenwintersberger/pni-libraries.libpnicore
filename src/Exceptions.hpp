//Exceptions for all classes

#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__

#include<iostream>
#include<string>

namespace pni{
namespace utils{


//! Exceptions base class

//! The base class for all exceptions in the library. Constructors are design
//! to take either const char * values or const std::string references as
//! valid input arguments. This should provide maximum flexibility in exception
//! creation.
class Exception{
    protected:
        std::string _name;  //!< name of the exception
        std::string _who;   //!< issuer of the exception
        std::string _desc;  //!< description of the error occured
    public:
        //! default constructor
        Exception(){}
        //! constructor with name as string

        //! \param n name of the exception
        Exception(const std::string &n);
        //! constructor with name as const char*

        //! \param n name of the exception
        Exception(const char *n);
        //! constructor with name and source as string objects

        //! \param n name of the exception
        //! \param w name or ID or the exceptions issuer
        Exception(const std::string &n,const std::string &w);
        //! constructor with name and source as const char*

        //! \param n name of the exception
        //! \param w name or ID of the exceptions issuer
        Exception(const char *n,const char *w);
        //! constructor with name, source, and description as string

        //! \param n name of the exception
        //! \param w name or ID of the exceptions issuer
        //! \param d description of the exception
        Exception(const std::string &n,const std::string &w,const std::string &d);
        //! constructor with name, source, and description as const char*

        //! \param n name of the exception
        //! \param w name or ID of the exceptions issuer
        //! \param d description of the exception
        Exception(const char *n,const char *w,const char *d);
        //! virtual destructor
        virtual ~Exception(){}
        
        //! set the exception name

        //! \param name exception name
        void setName(const char *name) { _name = std::string(name); }
        //! set the exception name

        //! \param name exception name
        void setName(const std::string &name) { _name = name; }
        //! get the exceptions name

        //! \return reference to the string object holding the name
        const std::string &getName() const { return _name;}

        //! set the exception issuer

        //! \param who name or some ID of the issuer
        void setSource(const char *who) { _who = who;}
        //! set the exception issuer

        //! \param who name or some ID of the issuer
        void setSource(const std::string &who) {_who = who;}
        //! get the exceptions issuer

        //! \return reference to the string object with the exceptions ID or name
        const std::string &getSource() const {return _who;}
        
        //! set exception description

        //! \param desc description of the exception
        void setDescription(const char *desc) {_desc = desc;}
        //! set exception desccription

        //! \param desc description of the exception
        void setDescription(const std::string &desc) {_desc=desc;}
        //! get the exceptions description

        //! \return reference to the string object with the exceptions description
        const std::string &getDescription() const {return _desc;}
        
        //! output operator for exceptions
        friend std::ostream &operator<<(std::ostream &,const Exception &);
        
};

//! memory allocation error

//! This exception is typically raised if memory allocation fails. In other words if
//! a call of the new operator returns NULL.
class MemoryAllocationError:public Exception{
    public:
		//! default constructor
        MemoryAllocationError():Exception("MemoryAllocationError"){}
        //! constructor

        //! \param who name or ID of the exceptions issuer
        //! \param desc description of the exception
        MemoryAllocationError(const std::string &who,const std::string &desc)
                                  :Exception("MemoryAllocationError",who,desc){}
        //! constructor

        //! \param w name or ID of the exceptions issuer
        //! \param d description of the exception
        MemoryAllocationError(const char *w,const char *d)
        					 :Exception("MemoryAllocationError",w,d){}
        //! destructor
        virtual ~MemoryAllocationError(){}
};

//! Shape mismatch error

//! This exception is usually raised in cases where array operations require shape matching
//! of the involved arrays but their shapes are different.
class ShapeMissmatchError:public Exception{
    public:
		//! default constructor
        ShapeMissmatchError():Exception("ArrayShapeMissmatchError"){}
        //! constructor

        //! \param who name or ID of the exceptions issuer
        //! \param desc description of the exception
        ShapeMissmatchError(const std::string &who,const std::string &desc)
            :Exception("ArrayShapeMissmatchError",who,desc){}
        //! constructor

        //! \param w name or ID of the exceptions issuer
        //! \param d description of the exception
        ShapeMissmatchError(const char *w,const char *d)
            :Exception("ArrayShapeMissmatchError",w,d){}
        //! destructor
        virtual ~ShapeMissmatchError(){}
        
};

//! Size missmatch error

//! This exception will be raised in cases where buffer sizes do not meet the
//! requirements. A typical situation would be that a buffer is passed to an Array
//! object whos size does not match the size given by the ArrayShape object of the
//! Array.
class SizeMissmatchError:public Exception{
public:
	//! default constructor
	SizeMissmatchError():Exception("SizeMissmatchError"){}
	//! constructor

	//! \param who name or ID of the exception issuer
	//! \param desc description of the exception
	SizeMissmatchError(const std::string &who,const std::string &desc)
	:Exception("SizeMissmatchError",who,desc){}
	//! constructor

	//! \param who name or ID of the exception issuer
	//! \param desc description of the exception
	SizeMissmatchError(const char *who,const char *desc)
	:Exception("SizeMissmatchError",who,desc){}

	//! destructor
	virtual ~SizeMissmatchError(){}
};

//! index error

//! Raised typically in cases where the [] operator is used to access a data element but the
//! provided index goes beyond the address space of the buffer or array.
class IndexError:public Exception{
public:
	//! default constructor
	IndexError():Exception("IndexError"){}
	//! constructor

	//! \param who name or ID of the exceptions issuer
	//! \param desc description of the exception
	IndexError(const std::string &who,const std::string &desc)
	:Exception("IndexError",who,desc){}
	//! constructor

	//! \param w name or ID of the exceptions issuer
	//! \param d description of the exception
	IndexError(const char *w,const char *d)
	:Exception("IndexError",w,d){}
	//! destructor
	virtual ~IndexError(){}
};

//! file error

//! Raised typically in case of File IO problems
class FileError:public Exception{
public:
	//! default constructor
	FileError():Exception("FileError"){}
	//! constructor

	//! \param w name or ID of the exception issuer
	//! \param d description of the exception
	FileError(const std::string &w,const std::string &d)
	:Exception("FileError",w,d){}
	//! constructor

	//! \param w name or ID of the exception issuer
	//! \param d description of the exception
	FileError(const char *w,const char *d)
	:Exception("FileError",w,d){}
	//! destructor
	virtual ~FileError(){}

};

}
}
#endif
