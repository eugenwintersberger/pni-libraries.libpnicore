#!/bin/bash


exec arrays/arrays_test &> /dev/null
tail arrays/arrays_test.xml

exec config/config_test &> /dev/null
tail config/config_test.xml

exec dim_layout_test/dim_layout_test &> /dev/null
tail dim_layout_test/dim_layout_test.xml

exec index_maps/index_maps_test &> /dev/null
tail index_maps/index_maps_test.xml

exec math/math_test &> /dev/null
tail math/math_test.xml

exec type_erasures/type_erasures &> /dev/null
tail type_erasures/type_erasures.xml

exec types/types_test &> /dev/null
tail types/types_test.xml

exec utils_test/utils_test &> /dev/null
tail utils_test/utils_test.xml

