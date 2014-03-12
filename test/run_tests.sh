#!/bin/bash


arrays/arrays_test &> arrays_test.log
#tail arrays_test.xml

config/config_test &> config_test.log
#tail config_test.xml

dim_layout_test/dim_layout_test &> dim_layout_test.log
#tail dim_layout_test.xml

index_maps/index_maps_test &> index_maps_test.log
#tail index_maps_test.xml

math/math_test &> math_test.log
#tail math_test.xml

type_erasures/type_erasures &> type_erasures.log
#tail type_erasures.xml

types/type_test &> type_test.log
#tail types_test.xml

utils_test/utils_test &> utils_test.log
#tail utils_test.xml

grep FailuresTotal *.xml

