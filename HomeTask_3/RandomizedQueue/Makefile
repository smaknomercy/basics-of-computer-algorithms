CC = gcc
CXX = g++

CFLAGS = -Wall -g -std=c11

CXXFLAGS = -Wall -g -std=c++20 -I/opt/homebrew/opt/googletest/include

GTEST_LIBS = -lgtest -lgtest_main -pthread

TEST_DIR = .

LDFLAGS = -L/opt/homebrew/opt/googletest/lib

SRCS = RandomizedQueue.c
TEST_SRC = tests.cpp

OBJS = $(SRCS:.c=.o) $(TEST_SRC:.cpp=.o)

TARGET = my_randomized_queue_test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(GTEST_LIBS) $(LDFLAGS)

RandomizedQueue.o: RandomizedQueue.c
	$(CC) $(CFLAGS) -I/opt/homebrew/opt/googletest/include -c $< -o $@

test.o: tests.cpp
	$(CXX) $(CXXFLAGS) -I/opt/homebrew/opt/googletest/include -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)