%%% description of how to use the library 

==================
Using `libpnicore`
==================


Include files
=============

To use `libpnicore` in code the appropriate header files must be included. In
the simplest case just use the :file:`core.hpp` file 

.. code-block:: cpp

    #include <pni/core.hpp>

which pulls in all the other header files required to work with `libpnicore`.
Alternatively, the header files for the different components provided by
`libpnicore` can be used

.. code-block:: cpp

    #include <pni/core/algorithms.hpp>    //basic algorithms
    #include <pni/core/arrays.hpp>        //multidimensional arrays
    #include <pni/core/benchmark.hpp>     //benchmark classes
    #include <pni/core/configuration.hpp> //program configuration facilities
    #include <pni/core/error.hpp>         //exception management
    #include <pni/core/type_erasures.hpp> //type erasures
    #include <pni/core/types.hpp>         //fundamental data types
    #include <pni/core/utilities.hpp>     //general purpose utilities

All classes provided by `libpnicore` reside within the
`pni::core` namespace. If you do not want to give the namespace
explicitly for every type and function use

.. code-block:: cpp
    
    using namespace pni::core;

after including the required header files.

Building and linking
====================

`libpnicore` provides a :command:`pkg-config` file. In the case of a system wide
installation this file is most probably allready at the right place in the file
system. One can easily check this with 

.. code-block:: bash

    $ pkg-config --libs --cflags pnicore 
    -lpniio -lhdf5 -lz -lboost_filesystem -lpnicore -lboost_program_options\ 
    -lboost_regex -lboost_system 

For installation locations which are not in the default paths of your system
you may get some additional :option:`-I` and :option:`-L` output pointing to
the directories where the header files and the library binaries are installed.
If :program:`pkg-config` complains that it cannot find a package named
:samp:`pnicore`
then you most probably have to set :envvar:`PKG_CONFIG_PATH` to the location
where the :program:`pkg-config` file of your `libpnicore` installation has been
installed. 


From the command line
---------------------

If a single simple program should be compiled the following approach is
suggested 

.. code-block:: bash

   $ g++ -std=c++11 -O3 -oprogram program.cpp $(pkg-config --cflags --libs pnicore)

Please recognize the :option:`-std=c++11` option. `libpnicore` requires a state
of the art compiler with full support for C++11.

From within a Makefile
----------------------

If :program:`make` should be used to build the code add the following lines to your
:file:`Makefile`

.. code-block:: make

    CPPFLAGS=-g -O3 -std=c++11 -fno-deduce-init-list -Wall -Wextra -pedantic \
             $(shell pkg-config --cflags pnicore) 
    LDFLAGS=$(shell pkg-config --libs pnicore)

This will set the appropriate compiler and linker options for the build.

With Scons
----------

If you use :program:`sons` for building the code add the following to your 
:file:`SConstruct` file

.. code-block:: python

   env = Environment()
   env.AppendUnique(CXXFLAGS=["-std=c++11","-pedantic","-Wall","-Wextra"])
   env.ParseConfig('pkg-config --cflags --libs pnicore')

The :py:meth:`ParseConfig` method of a :program:`scons` environment is able
to parse the output of :program:`pkg-config` and add the flags to the
environments configuration.

With CMake
----------

Currently no `cmake`-package files are installed with the library. However, due
to :program:`cmake` s :program:`pkg-config` support autoconfiguration can still
be done. In one of the toplevel :file:`CMakeLists.txt` files use

.. code-block:: cmake
    
    pkg_search_module(PNICORE REQUIRED pnicore)

to load the configuration for `libpnicore` from :program:`pkg-config`.
Furthermore we have to add the header file and library installation paths to
the configuration

.. code-block:: cmake

   link_directories(${PNICORE_LIBRARY_DIRS} ${HDF5_LIBRARY_DIRS})
   include_directories(${PNICORE_INCLUDE_DIRS} ${HDF5_INCLUDE_DIRS})

Finally the library can easily be added to the build target with 

.. code-block:: cmake

   target_link_libraries(mytarget ${PNICORE_LIBRARIES})

