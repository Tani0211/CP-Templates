# Compiler settings — C++17, warnings on, include repo root so tests can #include "../Category/File.cpp"
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I..

# Auto-discover every test_*.cpp in this directory
SRCS := $(wildcard test_*.cpp)
BINS := $(SRCS:.cpp=)

# Default target: build all test binaries
all: $(BINS)

# Pattern rule: compile each test_foo.cpp → test_foo binary
%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Run all binaries; count failures and exit non-zero if any test failed
run: all
	@failed=0; \
	for t in $(BINS); do \
	  ./$$t || failed=$$((failed + 1)); \
	done; \
	if [ $$failed -eq 0 ]; then echo "All tests passed."; else echo "$$failed test(s) failed."; fi; \
	exit $$failed

# Remove compiled binaries
clean:
	rm -f $(BINS)

.PHONY: all run clean
