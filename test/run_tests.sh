#!/bin/bash


arrays/arrays_test &> /dev/null
#tail arrays_test.xml

config/config_test &> /dev/null
#tail config_test.xml

dim_layout_test/dim_layout_test &> /dev/null
#tail dim_layout_test.xml

index_maps/index_maps_test &> /dev/null
#tail index_maps_test.xml

math/math_test &> /dev/null
#tail math_test.xml

type_erasures/type_erasures &> /dev/null
#tail type_erasures.xml

types/type_test &> /dev/null
#tail types_test.xml

utils_test/utils_test &> /dev/null
#tail utils_test.xml

grep FailuresTotal *.xml

