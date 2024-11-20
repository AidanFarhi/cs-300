CXX = g++
CXXFLAGS = -std=c++11
SOURCES = CSVparser.cpp HashTable.cpp
TARGET = hash_table

build: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
