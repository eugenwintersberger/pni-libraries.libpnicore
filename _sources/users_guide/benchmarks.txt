==========
Benchmarks
==========

To check the overall performance of the :cpp:class:`mdarray` template provided by the
library benchmark programs have been written whose results will be presented in
this chapter.  
Three particular aspects are investigated by the benchmarks 

* linear data access via iterators
* data access via multidimensional indexes 
* performance of the arithmetic operators

To keep the number of benchmark results within reasonable bounds all benchmarks
have been performend with the three predefined specializations of the
:cpp:class:`mdarray` template: :cpp:class:`dynamic_array`, 
:cpp:class:`fixed_dim_array`, and :cpp:class:`static_array`. In addition to 
the plain array templates also their view types have been taken into 
account. The view types are interesting as they add
some additional code which may cause some overhead. 

Its (presumed) outstanding performance is the reason why so much scientific
software is written in C. In order to show that the code provided by
*libpnicore* can be used in high performance applications all benchmarks are
normalized to the runtime of equivalient C code. In most situations this means
that data access is done via simple pointers.


Iterator benchmarks
===================

Results for the iterator benchmark. *r* and *w* denote reading and
writing results respectively.

+------------------------------+----------------+---------------------+
| array type                   | iterator (r/w) | view iterator (r/w) |
+==============================+================+=====================+
| :cpp:class:`dynamic_array`   | 1.02/1.04      | 2.50/2.96           |
+------------------------------+----------------+---------------------+
| :cpp:class:`fixed_dim_array` | 0.99/1.00      | 2.52/2.89           |
+------------------------------+----------------+---------------------+
| :cpp:class:`static_array`    | 1.00/1.00      | 2.07/2.40           |
+------------------------------+----------------+---------------------+

All numbers in this table are normalized to the raw pointer performance 
and thus reflect directly any performance penalty or advantage over 
direct pointer access. Only the :cpp:class:`dynamic_array` class shows 
a small performance penalty of 2 to 4 % over the C code. The other 
two array classes run as fast as plain C programs. 

In all cases iterating over a view shows significant performance penalties. 
Using iterators on views is about 2 up to 3 times slower than accessing 
the data via a pointer. This is simply due to additional overhead the 
view template introduces. 

The iterator write benchmarks run basically the following code for 
*libpnicore*

.. code-block:: cpp
   
   for(auto &x: data) 
       x = buffer;

which must compete with 

.. code-block:: c

   T *data = new T[N];
   
   for(size_t i=0;i<N;++i) 
       data[i] = buffer;

in C. For the read benchmark C++ uses essentially 

.. code-block:: cpp

   for(auto x: data)
       buffer = x;

and C 

.. code-block:: cpp

   T *data = new T[N];
   
   for(size_t i=0;i<N;++i)
       buffer = data[i];

For both C-codes the performance measurements have been done without 
the time required to allocate memory. 


Multidimensional index access
=============================


One of the major goals for *libpnicore* was to provide an array type which is as
easy and intuitive to use as the multidimensional array types provided by
Fortran or the numpy Python package. This includes easy access to array elements
using a multidimensional index which can be passed either as a variadic list of 
integers or as a container of an integer type. 
This immediately raises the question how fast data access via multidimensional 
indices is  in comparison with simple pointer access where the linear offset is
computed from the multidimensional index and the number of elements along each
dimension of the array. 

Results for the muldimensional index access benchmarks. For array views a 
significant overhead is added. This makes views at the current state of
development rather useless for high performance applications.

+-----------------------------------+----------------+--------------+-------------+
| array type                        | variadic (r/w) | vector (r/w) | array (r/w) |
+===================================+================+==============+=============+
| :cpp:class:`dynamic_array`        | 1.03/1.02      | 3.82/4.63    | 3.33/3.76   |
+-----------------------------------+----------------+--------------+-------------+
| :cpp:class:`dynamci_array`-view   | 3.39/6.31      | 6.29/6.49    | 4.23/5.41   |
+-----------------------------------+----------------+--------------+-------------+
| :cpp:class:`fixed_dim_array`      | 0.94/0.97      | 3.27/3.79    | 3.29/3.53   |
+-----------------------------------+----------------+--------------+-------------+
| :cpp:class:`fixed_dim_array`-view | 3.27/6.04      | 5.02/6.26    | 4.03/5.15   |
+-----------------------------------+----------------+--------------+-------------+
| :cpp:class:`static_array`         | 0.97/0.97      | 3.08/3.75    | 3.25/3.67   |
+-----------------------------------+----------------+--------------+-------------+
| :cpp:class:`static_array`-view    | 2.78/3.58      | 4.66/5.92    | 4.83/5.33   |
+-----------------------------------+----------------+--------------+-------------+

For C++ writing the loop look basically like this 

.. code-block:: cpp

   //with variadic access
   for(size_t i=0;i<nx;++i)
       for(size_t j=0;j<ny;++j)
           data(i,j) = buffer;

   //std::vector or std::array access
   for(index[0]=0;index[0]<nx;++index[0])
       for(index[1]=0;index[1]<ny;++index[1])
           data(index) = buffer;

The C writing loop has the basic structure

.. code-block:: c

   for(size_t i=0;i<nx;++i)
       for(size_t j=0;j<ny;++j)
           data[i*ny+j] = buffer;

For reading access the loops are the same only the rhs and lhs of the assignment 
operators are flipped.

It follows immediately from this table that passing the multidimensional index
as a variadic argument list is the fastest way of how to access the data. 
The performance is virtually equal to those of using direct pointer access. 
Using the container types :cpp:class:`std::vector` or :cpp:class:`std::array` to 
pass the index will cause in a performance penalty of 200 to 300 % for 
virtually all array types. 
As with linear access via iterators, there is a significant performance penalty
when accessing data via a view. One surprising aspect of the results is the fact 
that at least for :cpp:class:`fixed_dim_array` and :cpp:class:`static_array` 
variadic access outperforms even pointer access.

The reasons for the huge performance penalties are yet unclear. However, we hope
that they can be reduced in further releases. 

Arithmetics
===========

Last but not least a feasible  array type has to provide arithmetic operators 
of reasonable performance. This last section compares the unary and binary
arithmetic operators for the :cpp:class:`mdarray specializations. 
Unlike for the other benchmarks the arithmetic benchmarks cover only the 
:cpp:class:`dynamic_array` and :cpp:class:`fixed_dim_array` specializations of 
:cpp:class:`mdarray`.

Unary arithmetics
-----------------

*libpnicore* s :cpp:class:`mdarray` template provides the following unary arithmetic
operators

* :cpp:any:`+=` unary addition
* :cpp:any:`-=` unary subtraction
* :cpp:any:`*=` unary multiplication
* :cpp:any:`/=` unary division

where the operations are applied element-wise on the LHS of the operator.
All operators accept either an array type or a scalar type as their RHS.
In the following table *a* and *b* denote arrays while *s* denotes a scalar.

+-----------------+----------------------------+------------------------------+
| operation       | :cpp:class:`dynamic_array` | :cpp:class:`fixed_dim_array` |
+=================+============================+==============================+
| :cpp:any:`a*=b` | 1.00                       | 1.00                         |
+-----------------+----------------------------+------------------------------+
| :cpp:any:`a*=s` | 0.77                       | 0.77                         |
+-----------------+----------------------------+------------------------------+
| :cpp:any:`a/=b` | 1.00                       | 1.00                         |
+-----------------+----------------------------+------------------------------+
| :cpp:any:`a/=s` | 1.00                       | 1.00                         |
+-----------------+----------------------------+------------------------------+
| :cpp:any:`a+=b` | 1.00                       | 1.00                         |
+-----------------+----------------------------+------------------------------+
| :cpp:any:`a+=s` | 0.77                       | 0.77                         |
+-----------------+----------------------------+------------------------------+
| :cpp:any:`a-=b` | 1.00                       | 1.00                         |
+-----------------+----------------------------+------------------------------+
| :cpp:any:`a-=s` | 0.77                       | 0.77                         |
+-----------------+----------------------------+------------------------------+

Both benchmarked types show rather 
similar performance. It is interesting, however, that in some cases the array
types seem to outperform the pointer implementation.

Binary arithmetics
------------------

Though also the binary operators accepts mixed array/scalar input, we have only 
benchmarked the array/array versions of the operators. 

+--------------------------+----------------------------+------------------------------+---------+
| operation                | :cpp:class:`dynamic_array` | :cpp:class:`fixed_dim_array` | Fortran |
+==========================+============================+==============================+=========+
| :cpp:any:`a+b`           | 1.04                       | 1.00                         | 2.18    |
+--------------------------+----------------------------+------------------------------+---------+
| :cpp:any:`a-b`           | 1.02                       | 1.00                         | 2.18    |
+--------------------------+----------------------------+------------------------------+---------+
| :cpp:any:`a*b`           | 1.05                       | 1.00                         | 2.24    |
+--------------------------+----------------------------+------------------------------+---------+
| :cpp:any:`a/b`           | 1.02                       | 1.00                         | 1.46    |
+--------------------------+----------------------------+------------------------------+---------+
| :cpp:any:`a*b + (d-e)/f` | 1.04                       | 1.00                         | 1.49    |
+--------------------------+----------------------------+------------------------------+---------+

As already mentioned binary arithmetic operations are implemented with
expression templates. Though the reference for the binary benchmarks are still
their equivalent C expressions Fortran has also been included in the benchmark. 
This is in so far of importance as Fortran is, until today, considered the
ultimate language for numerics. 
The first conclusion which can be drawn from
this table is the fact that :cpp:class:`dynamic_array` shows an up to 5 % 
performance penalty over C code while :cpp:class:`fixed_dim_array` is virtually as
fast as the C implementation of the tested operations. 
The most astonishing result is, however, the rather low performance of Fortran
not only in comparison with the C++ types but also with respect to the C
implementation of the operations (as can be seen from the last column of the above 
table. 

The reason for the bad performance is not yet clear. It might be due to the poor
quality of the compiler (we only tested with :program:`gfortran` from the GNU
compiler collection). Thus the tests should be repeated using for instance
Intel's compiler suite. On the other handside: the GNU compiler collection is
the most important for our uses which makes the results for this set of
compilers the most relevant. Another reason might be that the benchmark code is
written in C++ and the Fortran functions are linked into the C++ code
statically. It may be possible that this has some negative effect on the
performance of the Fortran code. Whatever might be the reason far the bad
Fortran results, a single conclusion can be drawn from this benchmark: 
Expression templates are a very sensible way to implement operators in C++ and
may can help to push C++ in the field of scientific computing.
