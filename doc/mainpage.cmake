/*! \mainpage @CMAKE_PROJECT_NAME@ @LIBRARY_VERSION@ documentation

Libpnicore is a utility library for a bunch of PNI related libraries. 
It provides the basic data structures and type definitions as well as 
type conversion facilities needed to write reliable code. 

This is the API documentation for libpnicore. If you are interested in a more
general discussion about the library and its components please read the 
uses guide or the administrators guide.  
*/


//=============================================================================
/*! \defgroup utility_classes Utility classes
This module contains utilty classes used throughout the entire code. 
*/

//=============================================================================
/*! \defgroup type_classes Data type related classes
    Data types and their correct handling plays an important role for 
    experiment data. This module contains all type definitions and classes 
    to obtain information from a type as well as converting types from one 
    to each other. \c libpninx basically follows the type conversion strategies
    of C++ with some exceptions. For instance, unlike in C++ conversion from
    floating point type to integer types is prohibited. This should avoid
    unintentional round-off errors that would occur during such a conversion. 
*/

/*!
\ingroup type_classes
\defgroup type_classes_internal Internal classes for type management

These classes are usually not intended to be used by library users. However, for
library developers this information can be useful.
*/

//=============================================================================
/*!
\defgroup type_erasure_classes Type Erasures

In \c libpnicore all objects are strongly typed. Somtimes this is a problem. For
this purpose several type erasures are provided to get around such situations. 
Type erasures exist for 

\li scalar values
\li references to scalar values
\li arrays 

*/

/*!
\ingroup type_erasure_classes
\defgroup type_erasure_classes_internal Interal classes

This section describes classes used by the type erasure classes internally and
is thus only interesting for library developers.
*/
//=============================================================================
/*! 
\defgroup mdim_array_classes Multidimensional arrays
*/

/*!
\ingroup mdim_array_classes
\defgroup mdim_basic_array_classes Basic arrays
*/

/*! 
\ingroup mdim_array_classes 
\defgroup index_mapping_classes Index mapper types

Index mappers compute the linear offset from a multidimensional index and vica
versa.
*/

/*!
\ingroup mdim_array_classes
\defgroup dim_layout_classes Dimension layout classes

Dimension layouts describe the logical structure of a multidimensional array.

*/

/*! 
\ingroup mdim_array_classes
\defgroup numeric_array_classes Numeric arrays
*/


//=============================================================================
/*! \defgroup iterator_types Iterators types of libpnicore
*/

/*! \defgroup error_classes Exception classes

In version 0.2.5 the exception backend has undergone a major rewrite. 
The old macros are no longer available. Exceptions provide much more detailed
information about where they are thrown and can be stacked to provide a kind of
stack trace where an exception has occurred and how it was propagated through the
code.
All information where an exception occurred is stored in an instance of
ExceptionRecord. An instance of this class can easily created using the 
EXCEPTION_RECORD macro (as in most cases the construction of an ExceptionRecord
will look equal). An exception record includes the exact signature of the method
or function, the line in the file, and the source file name where the exception
was thrown.
This should make it easier to identify the location where an exception occurred. 

*/




