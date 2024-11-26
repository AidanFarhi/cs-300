CXX = g++
CXXFLAGS = -std=c++11
SOURCES = CSVparser.cpp BinarySearchTree.cpp
TARGET = BinarySearchTree

build: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)