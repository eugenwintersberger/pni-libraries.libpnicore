=============================== 
Program configuration utilities
===============================

One of the most tedious tasks when writing applications is how to handle its
configuration. There are several possibilities how a user can tell a program
about input arguments and parameters 

* via command line options and arguments
* via environment variables of the calling shell
* and via configuration files.

It is important to note that this is information the program has only read-only
access too. *libpnicore* provides some simple functions to make programs aware
of command line options and arguments as well as of configuration files. The
facility provided by *libpnicore* is based on the :cpp:any:`boost::program_options`
library. However, its interface is much easier to use.  
What makes this facility so interesting for scientific applications is the fact
that every option or argument can be given a distinct data type. 

Command line options and arguments
==================================

One possibility to provide information to a program is by means of command line
arguments and options which are passed to the program when called from a shell
by the user. This is particularly true for Unix systems where many programs are
called via the command line rather than via a Desktop. 

In this section we will deal with all the basics required to use *libpnicore* s
configuration facilities. Read this in any case even if you only want to use a
configuration file as many of the things written is true also for configuration
files. 

Unix conventions
----------------


In the Unix world we have to distinguish between command line *arguments*
and *options*. The former ones are strings which can typically appear
anywhere in the command calling the program from the shell. The meaning of a
particular option depends only on its position within the command used to run a
program. 
The latter ones, *options*, are introduced by special tokens in the calling
command. This token determines the meaning of a particular option. Thus options
can appear in any order after the name of the program. 
To get a better feeling about arguments and options lets have a look on a
typical command line call on a Unix or Linux system

.. code-block:: bash

   > program -oresult.dat --wavelength=1.234 in1.dat in2.dat in3.dat

The three input files at the end of the call (:file:`in1.dat`, :file:`in2.dat`, and
:file:`in3.dat`) are passed as arguments. They can appear in any order and there
is no way to distinguish one from the other and will be processed in the order
of their appearance. This is in contrast to :file:`result.dat` and `1.234`
which are passed as options. An option can be identified by a *short name* (by
convention this must be a single character) as it is the case for :file:`result.dat` 
or by a *long name*, like for `1.234`, which must be a
string without whitespaces. Short names are are introduced by a single `-`
and followed immediately by the value of the option. Long names start with
`--` followed by a `=` and the value of the option. An option can have both,
a long and a short name. While short names are typically used when a program is
called interactively by a user to minimize the typing effort, long names are
mostly used when a program is called from a script. As they are not limited to a
single character long names can be chosen much more descriptive than short
names. Being restricted to a single character short names are sometimes only
used for options which are frequently used in interactive calls while scarcely
used options have only a long name.

Creating a simple program configuration
---------------------------------------

Creating a configuration for a program involves three classes

* :cpp:class:`configuration` which, in the end, will hold the configuration data and provide access to it.
* :cpp:class:`config_option` describing a single command line option
* :cpp:class:`config_argument` which we will use to describe command line arguments 

Lets start with the above example. The source code of the program would maybe
look like this

.. code-block:: cpp
   
   #include <vector>
   #include <pni/core/types.hpp>
   #include <pni/core/config/configuration.hpp>
   #include <pni/core/config/config_parser.hpp>
   
   using namespace pni::core;
   
   typedef std::vector<string> input_files;
   
   int main(int argc,char **argv)
   {
       configuration config;
       config.add_option(config_option<string>("output","o","output file"));
       config.add_option(config_option<float64>("wavelength","w"));
       config.add_argument(config_argument<input_files>("input",-1));
   
       parse(config,cliargs2vector(argc,argv));
   
       return 0;
   }

Configuration files
===================

Configuration files handled by *libpnicore* follow the `INI`-file syntax as
used by Windows. 
An example file would look like this

.. code-block:: ini

   #experiment.cfg
   [beam]
   wavelength = 1.543
   divergence = 0.12
   diameter   = 1.23
   
   [sample]
   name = sample1
   description = first sample in the series

To read this file create the following configuration in the program

.. code-block:: cpp

   #include <pni/core/types.hpp>
   #include <pni/core/configuration.hpp>
   #include <pni/core/config_parser.hpp>
   
   using namespace pni::core;
   
   int main(int argc,char **argv)
   {
       configuration config;
   
       config.add_option(config_option<float64>("beam.wavelength",""));
       config.add_option(config_option<float64>("beam.divergence",""));
       config.add_option(config_option<float64>("beam.diameter",""));
       config.add_option(config_option<string>("sample.name",""));
       config.add_option(config_option<string>("sample.description",""));
   
       parse(config,"experiment.cfg");
   
       //use the options
   }


Using configuration files and command line options together
===========================================================

.. todo::

   Need to add some content here

