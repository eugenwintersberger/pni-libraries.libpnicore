==========================
Multidimensional array API
==========================

:cpp:class:`mdarray`
====================

.. doxygenclass:: pni::core::mdarray
   :members:

:cpp:class:`array_view`
=======================

.. doxygenclass:: pni::core::array_view
   :members:


:cpp:class:`scalar`
===================

.. doxygenclass:: pni::core::scalar
   :members:
   
Operators
---------

.. doxygenfunction:: pni::core::operator==(const scalar< T > &, const scalar< T > &)

.. doxygenfunction:: pni::core::operator!=(const scalar< T > &, const scalar< T > &)

.. doxygenfunction:: pni::core::operator<<(std::ostream &, const scalar< T > &)

.. doxygenfunction:: pni::core::operator>>(std::istream &, scalar< T > &)
   
:cpp:class:`slice`
==================

.. doxygenclass:: pni::core::slice
   :members:
   
Functions
---------

.. doxygenfunction:: pni::core::size(const slice &)

.. doxygenfunction:: pni::core::span(const slice &)