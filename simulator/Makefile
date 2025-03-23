# generate makefile for test_Reg

# Makefile for Reg unit tests

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g
INCLUDES = -I. -I..

# Google Test libraries
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Source files and target
SRCS = counter.cpp
HEADERS = wildcard(*.h)
TARGET = $(basename $(SRCS))

# Default target
all: $(TARGET)

# Compile the test executable
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o $@ $(GTEST_LIBS)


# Run the tests
test: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(TARGET) *.o


.PHONY: all test clean