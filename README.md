# libpnicore
                                   

libpnicore is the foundation of the PNI library stack. It provides data structures
and functions used by all other libraries within the stack. These data
structures include

* a set of well defined data types along with utilities around them
* multidimensional arrays
* facilities to quickly implement command line options and arguments
  for programs
* type erasures for scalar and array objects
* a set of exceptions used by all other libraries 

## Installation

On Linux the following software is required to build the libpnicore

* [gcc](https://gcc.gnu.org/) >= 4.8
* [cmake](https://cmake.org/) >= 3.5
* [doxygen](http://www.stack.nl/~dimitri/doxygen/)
* [sphinx](http://www.sphinx-doc.org/en/stable/)
* [Boost](http://www.boost.org/) >= 1.55

Acquire the sources either by either cloning this repository or by 

```bash
$ git clone https://github.com/pni-libraries/libpnicore.git
```

alternatively you could also download a source tarball from the release 
site of this project. Once the you have the sources create a build 
directory and run cmake 

```bash
$ mkdir libpnicore-build
$ cd libpnicore-build
$ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/opt/pni ../libpnicore
```
In the example we have chosen to install the library below `/opt/pni`. 
To test build and install the library use 

```bash
$ make
$ make test
$ make install
```

## Usage

C
