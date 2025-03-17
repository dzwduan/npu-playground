# Makefile for the gemm_ws project

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = 

# Include paths
INCLUDES = -I.

# Source files
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = gemm_simulator

# External libraries
LIBS = -lspdlog

# Default target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(LIBS)

# Rule for .cpp -> .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Dependencies
main.o: main.cpp config.h mapping.h
mapping.o: mapping.cpp mapping.h
config.o: config.cpp config.h

# Clean up
clean:
	rm -f $(OBJS) $(TARGET) *~

# Phony targets
.PHONY: all clean