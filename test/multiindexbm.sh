#!/bin/bash

cmd=./multiindexbm
nruns=1000000
size="100 100"

$cmd ptr $nruns $size &> multiindexbm_ptr_100x100.dat
$cmd darray $nruns $size &> multiindexbm_darray_100x100.dat
$cmd ndarray $nruns $size &> multiindexbm_ndarray_100x100.dat
$cmd sarray $nruns $size &> multiindexbm_sarray_100x100.dat
