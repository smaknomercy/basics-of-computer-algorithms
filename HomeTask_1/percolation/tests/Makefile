# Makefile for unit testing

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -g -I/usr/include/gtest -I/opt/homebrew/opt/googletest/include -I$(PERCOLATION_DIR) -I$(DYNAMIC_CONNECTIVITY_DIR)
LDFLAGS = -L/opt/homebrew/opt/googletest/lib

# Google Test libraries
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Paths
PERCOLATION_DIR = ../src
DYNAMIC_CONNECTIVITY_DIR = ../../dynamic_connectivity/src
TEST_DIR = .

# Source and test files
SRC = $(PERCOLATION_DIR)/percolation.c $(DYNAMIC_CONNECTIVITY_DIR)/dynamic_connectivity.c
TEST_SRC = $(TEST_DIR)/percolation_tests.cpp

# Target executable
TARGET = percolation_tests

# Build rule
all: $(TARGET)

$(TARGET): $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST_SRC) -o $(TARGET) $(LDFLAGS) $(GTEST_LIBS)

# Clean rule
clean:
	rm -f $(TARGET) *.o