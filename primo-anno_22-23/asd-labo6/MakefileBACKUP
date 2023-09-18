CXX = g++
CXXFLAGS = -std=c++11 -Wall -DUSE_HASH_TABLE

SOURCES = dictionary-hashtable.cpp string-utility.cpp dictionary-main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

