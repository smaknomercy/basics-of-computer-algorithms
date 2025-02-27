# Makefile for unit testing

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -g -I/opt/homebrew/opt/googletest/include -I$(SRC_DIR)
LDFLAGS = -L/opt/homebrew/opt/googletest/lib

# Google Test libraries
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Paths
SRC_DIR = ../src
TEST_DIR = .

# Source and test files
SRC = $(SRC_DIR)/dynamic_connectivity.c
TEST_SRC = $(TEST_DIR)/dynamic_connectivity_tests.cpp

# Target executable
TARGET = dynamic_connectivity_tests

# Build rule
all: $(TARGET)

$(TARGET): $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST_SRC) -o $(TARGET) $(LDFLAGS) $(GTEST_LIBS)

# Clean rule
clean:
	rm -f $(TARGET) *.o