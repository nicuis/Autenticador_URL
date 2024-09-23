CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic

.PHONY: test clean

test:
	$(CXX) $(CXXFLAGS) -o build/url_validation_test test/url_validation_test.cpp src/validators/url_validator.cpp

clean-tests:
	rm -f build/*test