==========
Exceptions
==========

:cpp:class:`pni::core::exception_record`
========================================

.. doxygenclass:: pni::core::exception_record
   :members:
   
.. doxygenfunction:: operator<<(std::ostream &,const exception_record &)
   
:cpp:class:`pni::core::exception`
=================================

.. doxygenclass:: pni::core::exception
   :members:


Exception classes
-----------------

These classes have the same interface as :cpp:class:`pni::core::exception` but 
denote different failure situations.

.. doxygenclass:: pni::core::memory_allocation_error
   
.. doxygenclass:: pni::core::memory_not_allocated_error

.. doxygenclass:: pni::core::shape_mismatch_error

.. doxygenclass:: pni::core::size_mismatch_error

.. doxygenclass:: pni::core::index_error

.. doxygenclass:: pni::core::key_error

.. doxygenclass:: pni::core::file_error

.. doxygenclass:: pni::core::type_error

.. doxygenclass:: pni::core::value_error

.. doxygenclass:: pni::core::range_error

.. doxygenclass:: pni::core::not_implemented_error

.. doxygenclass:: pni::core::iterator_error

.. doxygenclass:: pni::core::cli_argument_error

.. doxygenclass:: pni::core::cli_option_error

.. doxygenclass:: pni::core::cli_error


Macros
======

.. doxygendefine:: EXCEPTION_RECORD

.. doxygendefine:: EXCEPTION_FORWARD


Utility functions
=================

.. doxygenfunction:: check_equal_size(const A &, const B &)

.. doxygenfunction:: check_equal_size(const A &, const B &, const exception_record &)