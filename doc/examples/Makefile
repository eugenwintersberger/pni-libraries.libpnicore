CPPFLAGS=-O2 -std=c++11 $(shell pkg-config --cflags pniutils) 
LDFLAGS=$(shell pkg-config --libs pniutils)

all: cbf_reader tif_reader fio_reader example_buffer1 example_buffer2 example_buffer3 example_array1 example_array2 example_array3 example_array4

cbf_reader: cbf_reader.cpp
	$(CXX) -o cbf_reader cbf_reader.cpp $(CPPFLAGS) $(LDFLAGS)

tif_reader: tif_reader.cpp
	$(CXX) -o tif_reader tif_reader.cpp $(CPPFLAGS) $(LDFLAGS)

fio_reader: fio_reader.cpp
	$(CXX) -o fio_reader fio_reader.cpp $(CPPFLAGS) $(LDFLAGS)

example_buffer1: example_buffer1.cpp
	$(CXX) -o example_buffer1 example_buffer1.cpp $(CPPFLAGS) $(LDFLAGS)

example_buffer2: example_buffer2.cpp
	$(CXX) -o example_buffer2 example_buffer2.cpp $(CPPFLAGS) $(LDFLAGS)

example_buffer3: example_buffer3.cpp
	$(CXX) -o example_buffer3 example_buffer3.cpp $(CPPFLAGS) $(LDFLAGS)

example_array1: example_array1.cpp
	$(CXX) -o example_array1 example_array1.cpp $(CPPFLAGS) $(LDFLAGS)

example_array2: example_array2.cpp
	$(CXX) -o example_array2 example_array2.cpp $(CPPFLAGS) $(LDFLAGS)

example_array3: example_array3.cpp
	$(CXX) -o example_array3 example_array3.cpp $(CPPFLAGS) $(LDFLAGS)

example_array4: example_array4.cpp
	$(CXX) -o example_array4 example_array4.cpp $(CPPFLAGS) $(LDFLAGS)

.PHONY: clean
	
clean:
	rm -f cbf_reader
	rm -f tif_reader
	rm -f fio_reader
	rm -f example_buffer1
	rm -f example_buffer2
	rm -f example_buffer3
	rm -f example_array1
	rm -f example_array2
	rm -f example_array3
	rm -f example_array4
