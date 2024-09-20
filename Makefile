CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic

.PHONY: test clean

test:
	$(CXX) $(CXXFLAGS) -o build/url_validation_test test/url_validation_test.cpp  

clean:
	rm -f build/url_validation_test