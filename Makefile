CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
EXCEPTIONS := src/exceptions/*.cpp
FILTERS =: src/filters/*.cpp

.PHONY: test clean

test:
	$(CXX) -o build/url_validation_test test/url_validation_test.cpp src/validators/url_validator.cpp $(FILTERS) $(EXCEPTIONS)

clean-tests:
	rm -f build/*test