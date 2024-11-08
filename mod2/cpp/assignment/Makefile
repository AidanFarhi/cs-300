# Makefile

# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++11

# Source files
SOURCES = CSVparser.cpp VectorSorting.cpp

# Executable name
TARGET = vector_sort

# The `build` target, used by running `make build`
build: $(TARGET)

# Link source files to create the executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Clean up compiled files
clean:
	rm -f $(TARGET)