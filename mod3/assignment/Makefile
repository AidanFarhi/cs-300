CXX = g++
CXXFLAGS = -std=c++11
SOURCES = CSVparser.cpp LinkedList.cpp
TARGET = linked_list

build: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)