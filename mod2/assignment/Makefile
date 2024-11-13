CXX = g++
CXXFLAGS = -std=c++11
SOURCES = CSVparser.cpp VectorSorting.cpp
TARGET = csv_parser

build: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)