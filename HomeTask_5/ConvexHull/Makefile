CC = gcc
CXX = g++
CFLAGS = -Wall -g -std=c11
CXXFLAGS = -Wall -g -std=c++20 -I/opt/homebrew/opt/googletest/include
GTEST_LIBS = -lgtest -lgtest_main -pthread
LDFLAGS = -L/opt/homebrew/opt/googletest/lib

TARGET = convex_hull
TEST_TARGET = convex_hull_test

OBJS = convex_hull.o main.o

TEST_OBJS = convex_hull.o test_convex_hull.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

convex_hull.o: convex_hull.c convex_hull.h
	$(CC) $(CFLAGS) -I/opt/homebrew/opt/googletest/include -c convex_hull.c -o convex_hull.o

main.o: main.c convex_hull.h
	$(CC) $(CFLAGS) -I/opt/homebrew/opt/googletest/include -c main.c -o main.o

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS) $(GTEST_LIBS) $(LDFLAGS)

test_convex_hull.o: test_convex_hull.cpp convex_hull.h
	$(CXX) $(CXXFLAGS) -I/opt/homebrew/opt/googletest/include -c test_convex_hull.cpp -o test_convex_hull.o

clean:
	rm -f *.o $(TARGET) $(TEST_TARGET)