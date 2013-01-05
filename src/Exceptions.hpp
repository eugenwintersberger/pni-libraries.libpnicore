/*
 * Declaration exception classes and related macros
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Declaration of the exception classes provided by the library along with
 * some macros that make using exceptions easier.
 *
 * Created on: Apr 19, 2011
 *     Author: Eugen Wintersberger
 *
 */

#pragma once

#include<iostream>
#include<string>
#include<exception>
#include<typeinfo>
#include<list>
#include<boost/current_function.hpp>

#include "Types.hpp"

namespace pni{
namespace core{

//================Macros related to exceptions==================================

/*!
\ingroup error_classes
\brief macro creating an instance of ExceptionRecord
*/
#define EXCEPTION_RECORD\
    ExceptionRecord(__FILE__,__LINE__,BOOST_CURRENT_FUNCTION)

/*! 
\ingroup error_classes
\brief forward an exception

This macro can be used to forward an exception caught from another function. It
appends the ExceptionRecord of the current function to the existing exception
and throws the exception again. Consider the following examples
\code
try { value = buffer.at(index); }
EXCEPTION_FORWARD(IndexError)
EXCEPTION_FORWARD(MemoryNotAllocatedError)
\endcode
Please note that the MUST NOT BE a semicolon at the end of this macro.
*/
#define EXCEPTION_FORWARD(ETYPE)\
    catch(ETYPE &error)\
    {\
        error.append(EXCEPTION_RECORD);\
        throw error;\
    }

    //========================Exception classes==================================
    /*!
    \ingroup error_classes
    \brief exception record 

    Contains the basic information where an exception has been thrown.  This
    information consists of the source file, the line in the file, and the
    signature of the function where the error occurred. 
    Using the BOOST_CURRENT_FUNCTION macro defined in boost/current_function.hpp
    such a record can easily be constructed with
    \code
    ExceptionRecord r(__FILE__,__LINE__,BOOST_CURRENT_FUNCTION);
    \endcode
    */
    class ExceptionRecord
    {
        private:
            String _file; //!< source file where the exception occured
            size_t _line; //!< line number in the source file
            String _function; //!< function in which the error occured
        public:
            //===================constructors and destructor===================
            //! no default constructor
            ExceptionRecord() = delete;

            //! constructor
            ExceptionRecord(const String &file,size_t line,const String &func):
                _file(file),
                _line(line),
                _function(func)
            {}

            //==================public member functions========================
            //! get file name
            const String &file() const { return _file; }
            //! get file line number
            size_t line() const { return _line; }
            //! get function
            const String &function() const { return _function; } 
    };

    /*!
    \ingroup error_classes
    \brief error record output operator
    */
    std::ostream &operator<<(std::ostream &o,const ExceptionRecord &rec); 

    //-------------------------------------------------------------------------
    /*!
    \ingroup error_classes
    \brief Exceptions base class

    This is the base class for all exceptions used in this library. 
    */
    class Exception:public std::exception{
        private:
            //! name of the exception
            String _name;
            //! description of the error occured
            String _description; 
            //! exception records
            std::list<ExceptionRecord> _records;
        protected:
            /*! \brief ouptut method

            Protected method to be used by derived classes for implementing 
            exception printing to std::out.
            \param o reference to the ouptput stream
            \return output stream
            */
            std::ostream &print(std::ostream &o) const;
    public:
        //===================public types======================================
        //! const iterator over the error record
        typedef std::list<ExceptionRecord>::const_iterator const_iterator;
        //===================constructors and destructor=======================
        //! default constructor
        Exception();

        //---------------------------------------------------------------------
        /*!
        \brief constructor with name as string

        \param n name of the exception
        */
        Exception(const String &n);

        //---------------------------------------------------------------------
        /*! 
        \brief  constructor with name and source as string objects

        \param n name of the exception
        \param rec Exception record of the initial location where the error
        occured
        */
        Exception(const String &n, const ExceptionRecord &rec);

        //---------------------------------------------------------------------
        /*!
        \brief constructor with name, source, and description as string

        \param n name of the exception
        \param rec exception record describing the location of the first
        occurrence  of the error
        \param d description of the exception
        */
        Exception(const String &n, const ExceptionRecord &rec, const String &d);

        //---------------------------------------------------------------------
        //! virtual destructor
        virtual ~Exception() throw() { }

        //===================public member functions===========================
        /*! 
        \brief set the exception name
        \param name exception name
        */
        void name(const std::string &name) { _name = name; }

        //---------------------------------------------------------------------
        /*!
        \brief get the exceptions name

        \return reference to the string object holding the name
        */
        const String &name() const { return _name; }

        /*!
        \brief add a new issuer

        Use this method to add a new issuer in the case that the exception 
        is re-thrown by an other function or class method.
        \code
        ...
        catch(Exception &error)
        {
            error.append(EXCEPTION_RECORD);
            throw error;
        }
        \endcode
        With this a particular exception can be traced througout the entire
        code.
        \param n ExceptionRecord to append 
        */
        void append(const ExceptionRecord &n) { _records.push_back(n); }

        //---------------------------------------------------------------------
        /*!
        \brief set exception desccription

        \param desc description of the exception
        */
        void description(const std::string &desc) { _description = desc; }

        //---------------------------------------------------------------------
        /*!
        \brief get the exceptions description

        \return reference to the string object with the exceptions description
        */
        const String &description() const { return _description; }

        /*! 
        \brief get iterator to first error record

        Return get a const iterator to the first error record in the class.
        \return iterator to first exception record
        */
        const_iterator begin() const { return _records.begin(); }

        /*!
        \brief get iterator to the last error record

        Return a const iterator pointing to the last+1 element in the exception
        record list. 
        \return iterator to last+1 exception record
        */
        const_iterator end() const { return _records.end(); }

        //---------------------------------------------------------------------
        //! output operator for exceptions
        friend std::ostream &operator<<(std::ostream &, const Exception &);
            
    };


    //--------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief memory allocation error

    This exception is typically raised when allocation of memory on the heap
    fails. In other words when a call to new leads to a nullptr.
    */
    class MemoryAllocationError: public Exception 
    {
        public:
            //! default constructor
            MemoryAllocationError() : Exception("MemoryAllocationError") 
            { }

            //! constructor

            //! \param i ExceptionRecord of the initial issuer
            //! \param d description of the exception
            explicit MemoryAllocationError(const ExceptionRecord &i, const String &d):
                Exception("MemoryAllocationError", i, d) 
            { }
            //! destructor
            ~MemoryAllocationError() throw() { } 

            //! output operator
            friend std::ostream &
                operator<<(std::ostream &o,const MemoryAllocationError &e);
    };

    //-------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief memory not allocated error

    This exception is usually thrown if one tries to access not allocated 
    memory.
    */
    class MemoryNotAllocatedError: public Exception
    {
        public:
            //! default constructor
            MemoryNotAllocatedError(): Exception("MemoryNotAllocatedError") 
            {}

            /*! 
            \brief constructor
            
            \param i ExceptionRecord of the initial location where the error
            occurred 
            \param d description of the error
            */
            explicit MemoryNotAllocatedError(const ExceptionRecord &i,const String &d):
                Exception("MemoryNotAllocatedError",i,d) 
            {}

            //! destructor
            ~MemoryNotAllocatedError() throw() {}

            //! output operator
            friend std::ostream &operator<<(std::ostream &o,const
                    MemoryNotAllocatedError &e);
    };


    //--------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief Shape mismatch error

    Raised in cases where the Shape objects of two objects are not equal.
    */
    class ShapeMissmatchError: public Exception 
    {
        public:
            //! default constructor
            ShapeMissmatchError() : Exception("ShapeMissmatchError") 
            { }

            /*! 
            \brief constructor

            \param i ExceptionRecord of the initial occurrence of the error
            \param d description of the exception
            */
            explicit ShapeMissmatchError(const ExceptionRecord &i, const String &d) :
                Exception("ShapeMissmatchError",i,d) 
            { }

            //! destructor
            ~ShapeMissmatchError() throw() { }

            //! output operator
            friend std::ostream &
                operator<<(std::ostream &o,const ShapeMissmatchError &e);
    };

    //--------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief Size missmatch error

    This exception will be raised in cases where buffer sizes do not meet the
    requirements.
    */
    class SizeMissmatchError: public Exception 
    {
        public:
            //! default constructor
            SizeMissmatchError() : Exception("SizeMissmatchError") 
            { }

            /*! 
            \brief constructor

            \param i ExceptionRecord of the initial occurrence of the error
            \param d description of the exception
            */
            explicit SizeMissmatchError(const ExceptionRecord &i, const String &d) :
                Exception("SizeMissmatchError", i,d) 
            { }

            //! destructor
            ~SizeMissmatchError() throw() { }

            //! output operator
            friend std::ostream &
                operator<<(std::ostream &o,const SizeMissmatchError &e);
    };

    //--------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief index error

    Raised if the index passed to a [] operator exceeds the size of the
    container it belongs to.
    */
    class IndexError: public Exception 
    {
        public:
            //! default constructor
            IndexError() : Exception("IndexError") 
            { }

            /*! 
            \brief constructor

            \param i ExceptionRecord of the initial occurrence of the error
            \param d description of the exception
            */
            explicit IndexError(const ExceptionRecord &i, const String &d) :
                Exception("IndexError", i, d) 
            { }
            
            //! destructor
            ~IndexError() throw() { }

            //! output operator
            friend std::ostream &
                operator<<(std::ostream &o,const IndexError &e);
    };

    //--------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief key error

    Raised in cases where a problem with the key of a hash map occurs.
    */
    class KeyError: public Exception
    {
        public:
            //! default constructor
            KeyError():Exception("KeyError"){}

            /*! 
            \brief constructor

            \param i ExceptionRecord of the initial occurrence of the error
            \param d description of the error
            */
            explicit KeyError(const ExceptionRecord &i,const String &d):
                Exception("KeyError",i,d)
            {}

            //! destructor
            ~KeyError() throw() {}

            //! output operator
            friend std::ostream &
                operator<<(std::ostream &o,const KeyError &e);
    };

    //--------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief file IO fails

    Raised typically in cases of problems with files.
    */
    class FileError: public Exception 
    {
        public:
            //! default constructor
            FileError() : Exception("FileError") { }

            /*! 
            \brief constructor

            \param i ExceptionRecord of the initial occurrence of the error
            \param d description of the exception
            */
            explicit FileError(const ExceptionRecord &i, const String &d) :
                Exception("FileError", i, d) 
            { }

            //! destructor
            ~FileError() throw() { }

            //! output operator
            friend std::ostream &
                operator<<(std::ostream &o,const FileError &e);

    };

    //------------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief data type error

    This exception is raised in cases of errors concerning data types.
    */
    class TypeError: public Exception 
    {
        public:
            //! default constructor
            TypeError() : Exception("TypeError") { }
            
            /*! 
            \brief constructor

            \param i ExceptionRecord of the initial occurrence of the error
            \param d error description as String
            */
            explicit TypeError(const ExceptionRecord &i, const String &d):
                Exception("TypeError", i, d) 
            { }

            //! destructor
            ~TypeError() throw() { }

            //! output operator
            friend std::ostream &
                operator<<(std::ostream &o,const TypeError &e);
    };

    //------------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief data range error

    This exception is raised in cases where data values exceed the range
    spanned by their data type.
    */
    class RangeError: public Exception 
    {
        public:
            //! default constructor
            RangeError(): Exception("RangeError"){ }

            /*! 
            \brief constructor

            Constructor setting source and description of the error
            \param i error issuer as string
            \param d error description as string
            */
            explicit RangeError(const ExceptionRecord &i,const String &d):
                Exception("RangeError",i,d)
            { }

            //! destructor
            ~RangeError() throw() { }

            //! output operator
            friend std::ostream &
                operator<<(std::ostream &o,const RangeError &e);
    };

    //--------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief not implemented exception

    This exception can be used to mark methods of abstract or base classes
    as not implemented. Such an approach can be quite useful for debugging
    and development.
    */
    class NotImplementedError:public Exception
    {
        public:
            //! default construtor
            NotImplementedError(): Exception("NotImplementedError"){ }

            /*! 
            \brief constructor

            \param i ExceptionRecord of the initial occurrence of the error
            \param d error description
            */
            explicit NotImplementedError(const ExceptionRecord &i,const String &d):
                Exception("NotImplementedError",i,d)
            { }

            //! destructor
            ~NotImplementedError() throw() { }

            //! output operator
            friend std::ostream &
                operator<<(std::ostream &o,const NotImplementedError &e);
    };


    //--------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief iterator error

    Exception thrown in case of iterator errors.
    */
    class IteratorError:public Exception
    {
        public:
            //! default constructor
            IteratorError():Exception("IteratorError"){ }

            /*! 
            \brief constructor

            Constructor setting the issuer and description of the error.
            \param i ExceptionRecord of the initial occurrence of the error
            \param d error description
            */
            explicit IteratorError(const ExceptionRecord &i,const String &d):
                Exception("IteratorError",i,d)
            { }

            //! destructor
            ~IteratorError() throw() { }

            //! output operator
            friend std::ostream &
                operator<<(std::ostream &o,const IteratorError &e);
    };
    

    //-------------------------------------------------------------------------
    /*!
    \brief command line argument error

    Thrown in cases where a command line argument (do not confuse this with an
    option has an inapropriate value or is missing).
    */
    class cli_argument_error:public Exception
    {
        public:
            //------------------------------------------------------------------
            //! default constructor
            cli_argument_error():Exception("CLIArgumentError"){}

            //------------------------------------------------------------------
            /*! 
            \brief constructor

            \param r exception record
            \param d description
            */
            cli_argument_error(const ExceptionRecord &r,const String &d):
                Exception("CLIArgumentError",r,d)
            {}
            
            //------------------------------------------------------------------
            //! destructor
            ~cli_argument_error() throw() {}

            //------------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,const cli_argument_error &e);
    };

    //--------------------------------------------------------------------------
    /*! 
    \brief command line option error

    Exception thrown in cases where a command line option is missing or has an
    inapropriate value.
    */
    class cli_option_error:public Exception
    {
        public:
            //------------------------------------------------------------------
            //! default constructor
            cli_option_error():Exception("CLIOptionError"){}

            //------------------------------------------------------------------
            /*!
            \brief constructor

            \param r exception record
            \param d description
            */
            cli_option_error(const ExceptionRecord &r,const String &d):
                Exception("CLIOptionError",r,d)
            {}

            //------------------------------------------------------------------
            ~cli_option_error() throw() {}

            //------------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,const cli_option_error &e);
    };

    //--------------------------------------------------------------------------
    /*!
    \brief general CLI error

    Thrown in case of a general CLI error not related to arguments or options.
    */
    class cli_error:public Exception
    {
        public:
            //------------------------------------------------------------------
            //! default constructor
            cli_error():Exception("CLIError"){}
            
            //------------------------------------------------------------------
            /*!
            \brief constructor

            \param r exception record
            \param d description
            */
            cli_error(const ExceptionRecord &r,const String &d):
                Exception("CLIError",r,d)
            {}

            //------------------------------------------------------------------
            //! destructor
            ~cli_error() throw() {}

            //------------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,const cli_error &e);
    };

    //--------------------------------------------------------------------------
    /*!
    \brief help request

    This is exception is not intended to manage an error at all. It is thrown in
    the case that a user makes a help request from the CLI.
    */
    class cli_help_request:public Exception
    {
        public:
            //------------------------------------------------------------------
            //! default constructor
            cli_help_request():Exception("CLIHelpRequest"){}
            
            //------------------------------------------------------------------
            /*!
            \brief constructor

            \param r exception record
            \param d description
            */
            cli_help_request(const ExceptionRecord &r,const String &d):
                Exception("CLIHelpRequest",r,d)
            {}

            //------------------------------------------------------------------
            //! destructor
            ~cli_help_request() throw() {}

            //! output operator
            friend std::ostream &operator<<(std::ostream &o,const cli_help_request &e);
    };
}
}
