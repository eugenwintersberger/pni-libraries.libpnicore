=============
Type erasures
=============

:cpp:class:`pni::core::value`
============================

.. doxygenclass:: pni::core::value
   :members:
   
Functions
---------

.. doxygenfunction:: pni::core::make_value

.. doxygenfunction:: pni::core::make_value(type_id_t)

.. doxygenfunction:: pni::core::type_id(const value &)


:cpp:class:`pni::core::value_ref`
=================================

.. doxygenclass:: pni::core::value_ref
   :members:
   
Functions
---------

.. doxygenfunction:: pni::core::to_value(const value_ref &)

:cpp:class:`pni::core::array`
=============================

.. doxygenclass:: pni::core::array
   :members:
   
Functions
---------

.. doxygenfunction:: pni::core::make_array(const STYPE &)

.. doxygenfunction:: pni::core::make_array(type_id_t, const CTYPE &)

.. doxygenfunction:: pni::core::type_id(const array &)
