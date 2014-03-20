CPPFLAGS=-g -O0 -std=c++11 -fno-deduce-init-list -Wall -Wextra -pedantic $(shell pkg-config --cflags pnicore) 
LDFLAGS=$(shell pkg-config --libs pnicore)

all: copy_file array_create array_inquery array_stl array_linear_access \
	array_multiindex array_view array_view_container array_arithmetic1 \
	array_arithmetic2 array_arithmetic3

copy_file: copy_file.cpp
	$(CXX) -o copy_file copy_file.cpp $(CPPFLAGS) $(LDFLAGS)

array_create: array_create.cpp
	$(CXX) -o array_create array_create.cpp $(CPPFLAGS) $(LDFLAGS)

array_inquery: array_inquery.cpp
	$(CXX) -o array_inquery array_inquery.cpp $(CPPFLAGS) $(LDFLAGS)

array_stl: array_stl.cpp
	$(CXX) -o array_stl array_stl.cpp $(CPPFLAGS) $(LDFLAGS)

array_linear_access: array_linear_access.cpp
	$(CXX) -o array_linear_access array_linear_access.cpp $(CPPFLAGS) $(LDFLAGS)

array_multiindex: array_multiindex.cpp
	$(CXX) -o array_multiindex array_multiindex.cpp $(CPPFLAGS) $(LDFLAGS)

array_view: array_view.cpp
	$(CXX) -o array_view array_view.cpp $(CPPFLAGS) $(LDFLAGS)

array_view_container: array_view_container.cpp
	$(CXX) -o array_view_container array_view_container.cpp $(CPPFLAGS) $(LDFLAGS)

array_arithmetic1: array_arithmetic1.cpp
	$(CXX) -o array_arithmetic1 array_arithmetic1.cpp $(CPPFLAGS) $(LDFLAGS)

array_arithmetic2: array_arithmetic2.cpp
	$(CXX) -o array_arithmetic2 array_arithmetic2.cpp $(CPPFLAGS) $(LDFLAGS)

array_arithmetic3: array_arithmetic3.cpp
	$(CXX) -o array_arithmetic3 array_arithmetic3.cpp $(CPPFLAGS) $(LDFLAGS)

.PHONY: clean
	
clean:
	rm -f file_copy
	rm -f array_create
	rm -f array_inquery
	rm -f array_stl
	rm -f array_linear_access
	rm -f array_multiindex
	rm -f array_view
	rm -f array_view_container
	rm -f array_arithmetic1
	rm -f array_arithmetic2
	rm -f array_arithmetic3
