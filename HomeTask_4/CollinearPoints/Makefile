CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c99 -g
CXXFLAGS = -Wall -Wextra -std=c++14 -g
TARGET_BRUTE = brute
TARGET_FAST = fast

TEST_DIR = test
GTEST_INCLUDE = /opt/homebrew/opt/googletest/include
GTEST_LIB = /opt/homebrew/opt/googletest/lib

all: $(TARGET_BRUTE) $(TARGET_FAST)

$(TARGET_BRUTE): Brute.o point.o
	$(CC) $(CFLAGS) -o $(TARGET_BRUTE) Brute.o point.o

$(TARGET_FAST): fast.o point.o
	$(CC) $(CFLAGS) -o $(TARGET_FAST) fast.o point.o

Brute.o: Brute.c point.h
	$(CC) $(CFLAGS) -c Brute.c

fast.o: fast.c point.h
	$(CC) $(CFLAGS) -c fast.c

point.o: point.c point.h
	$(CC) $(CFLAGS) -c point.c

test: test_run

test_run: test_point.o point.o
	$(CXX) $(CXXFLAGS) -o runTests test_point.o point.o -L$(GTEST_LIB) -lgtest -lgtest_main -pthread

test_point.o: test_point.cpp point.h
	$(CXX) $(CXXFLAGS) -I$(GTEST_INCLUDE) -c test_point.cpp

clean:
	rm -f $(TARGET_BRUTE) $(TARGET_FAST) *.o runTests
