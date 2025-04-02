CC = gcc
CXX = g++

CFLAGS = -Wall -g -std=c11

CXXFLAGS = -Wall -g -std=c++20 -I/opt/homebrew/opt/googletest/include

GTEST_LIBS = -lgtest -lgtest_main -pthread

TEST_DIR = .

LDFLAGS = -L/opt/homebrew/opt/googletest/lib

SRCS = Deque.c
TEST_SRC = tests.cpp

OBJS = $(SRCS:.c=.o) $(TEST_SRC:.cpp=.o)

TARGET = my_deque_test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(GTEST_LIBS) $(LDFLAGS)

Deque.o: Deque.c
	$(CC) $(CFLAGS) -I/opt/homebrew/opt/googletest/include -c $< -o $@

tests.o: tests.cpp
	$(CXX) $(CXXFLAGS) -I/opt/homebrew/opt/googletest/include -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)