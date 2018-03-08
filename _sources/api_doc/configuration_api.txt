=================
Configuration API
=================

:cpp:class:`cli_args`
=====================

.. doxygenclass:: pni::core::cli_args
   :members:
   
:cpp:class:`config_argument`
============================

.. doxygenclass:: pni::core::config_argument
   :members:
   
   
:cpp:class:`config_option`
==========================

.. doxygenclass:: pni::core::config_option
   :members:
   
:cpp:class:`configuration`
==========================

.. doxygenclass:: pni::core::configuration
   :members:


Functions
=========

.. doxygenfunction:: operator<<(std::ostream &, const cli_args &)

.. doxygenfunction:: cliargs2vector(int , char **)

.. doxygenfunction:: pni::core::parse(configuration &, const std::vector< string > &, bool)

.. doxygenfunction:: pni::core::parse(configuration &, const string &)
