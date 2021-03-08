# libpnicore
                                   

*libpnicore* is the foundation of the PNI library stack. It provides data structures
and functions used by all other libraries within the stack. These data
structures include

* a set of well defined data types along with utilities around them
* multidimensional arrays
* facilities to quickly implement command line options and arguments
  for programs
* type erasures for scalar and array objects
* a set of exceptions used by all other libraries 

## Installation

On Linux the following software is required to build the *libpnicore*

* [gcc](https://gcc.gnu.org/) >= 4.8
* [cmake](https://cmake.org/) >= 3.5
* [doxygen](http://www.stack.nl/~dimitri/doxygen/) to generate XML API documentation
* [sphinx](http://www.sphinx-doc.org/en/stable/) to generate HTML and PDF documentation
* [Boost](http://www.boost.org/) >= 1.60

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

*libpnicore* installs a CMake package file along with its files. So using the 
library from within CMake is rather simple. Your `CMakeLists.txt` includes
the `pnicore` package as any other package 

```cmake
cmake_minimum_required(VERSION 3.5.0)
project(test_pnicore LANGUAGES CXX C VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 11)

find_package(pnicore REQUIRED)

add_executable(test_pnicore test_pnicore.cpp)
target_link_libraries(test_pnicore pnicore_shared)
```

As we are relying on CMake version higher than 3.3 we can use the imported 
targets feature. In this case all dependencies required to build and link
with *libpnicore* are automatically pulled in by the `pnicore_shared` 
target. Be aware of the `CMAKE_CXX_STANDARD` variable set to `11` in the 
above example. This is absolutely mandatory if you want to use *libpnicore*!

In cases where you have *libpnicore* installed to locations where cmake 
is not automatically looking for packages you may have to set the 
`pnicore_DIR` variable when calling cmake the first time. 

More information can be found at [online documentation](https://pni-libraries.github.io/libpnicore/index.html).

Changes for a specific version of libpnicore can be found
at [ChangeLog](https://raw.githubusercontent.com/pni-libraries/libpnicore/develop/ChangeLog).