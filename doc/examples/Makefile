CPPFLAGS=-O2 -std=c++0x -fno-deduce-init-list $(shell pkg-config --cflags pnicore) 
LDFLAGS=$(shell pkg-config --libs pnicore)

all: fio_reader example_buffer1 example_buffer2 example_buffer3 example_array1 example_array2 example_array3 example_array4

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
	rm -f fio_reader
	rm -f example_buffer1
	rm -f example_buffer2
	rm -f example_buffer3
	rm -f example_array1
	rm -f example_array2
	rm -f example_array3
	rm -f example_array4
