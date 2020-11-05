==============================
Data types and type management
==============================


:cpp:enum:`pni::core::type_id_t`
================================

.. doxygenenum:: pni::core::type_id_t

Operators
---------

.. doxygenfunction:: operator<<(std::ostream &,const type_id_t &)

Predicates
----------

.. doxygenfunction:: is_numeric(type_id_t)

.. doxygenfunction:: is_integer(type_id_t)

.. doxygenfunction:: is_complex(type_id_t)

.. doxygenfunction:: is_float(type_id_t)

.. doxygenfunction:: is_checked_convertible(type_id_t,type_id_t)

.. doxygenfunction:: is_unchecked_convertible(type_id_t,type_id_t)

.. doxygenfunction:: is_convertible(type_id_t,type_id_t)


Utility functions
-----------------

.. doxygenfunction:: type_id_from_str(const string &)

.. doxygenfunction:: str_from_type_id(type_id_t)

.. doxygenfunction:: type_id(const T &)
   

:cpp:enum:`pni::core::type_class_t`
===================================

.. doxygenenum:: pni::core::type_class_t


:cpp:class:`pni::core::bool_t`
=============================

.. doxygenclass:: pni::core::bool_t
   :members:
   
   
:cpp:class:`pni::core::none`
============================

.. doxygenstruct:: pni::core::none
   :members:
   
Operators
---------

.. doxygenfunction:: operator<<(std::ostream &,const none &)

.. doxygenfunction:: operator>>(std::istream &,none &)

.. doxygenfunction:: operator==(const none &,const none &)

.. doxygenfunction:: operator!=(const none &,const none &)
   
   
:cpp:class:`pni::core::binary_t`
================================

.. doxygenclass:: pni::core::binary_t
   :members:
   
.. doxygenfunction:: pni::core::operator<<(std::ostream &, const binary_t< NTYPE > &)



