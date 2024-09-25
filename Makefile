CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -O3
EXCEPTIONS := src/exceptions/*.cpp
FILTERS := src/filters/*.cpp
IO := src/io/*.cpp
VALIDATORS := src/validators/*.cpp

.PHONY: all test clean clean-tests

all:
	$(CXX) $(CXXFLAGS) -o build/main main.cpp $(VALIDATORS) $(IO) $(FILTERS) $(EXCEPTIONS)

clean:
	rm -f build/*

test:
	$(CXX) $(CXXFLAGS) -o build/url_validation_test test/url_validation_test.cpp src/validators/url_validator.cpp $(FILTERS) $(EXCEPTIONS) -g

clean-tests:
	rm -f build/*test