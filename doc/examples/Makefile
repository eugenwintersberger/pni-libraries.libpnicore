CPPFLAGS=-g -O3 -std=c++11 -fno-deduce-init-list -Wall -Wextra -pedantic \
		 $(shell pkg-config --cflags pnicore) 
LDFLAGS=$(shell pkg-config --libs pnicore)
SOURCES=$(wildcard *.cpp)
PRGS=$(patsubst %.cpp,%,$(SOURCES))

all: $(PRGS)

$(PRGS):$(SOURCES)
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)


.PHONY: clean
	
clean:
	rm -f $(PRGS)
