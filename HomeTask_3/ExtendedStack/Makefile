CC = gcc
CXX = g++

CFLAGS = -Wall -g -std=c11

CXXFLAGS = -Wall -g -std=c++20 -I/opt/homebrew/opt/googletest/include

SRCS = Stack.c
TEST_SRC = main.cpp
OBJS = $(SRCS:.c=.o) $(TEST_SRC:.cpp=.o)

TARGET = stack_test

GTEST_LIBS = -lgtest -lgtest_main -pthread

LDFLAGS = -L/opt/homebrew/opt/googletest/lib

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(GTEST_LIBS) $(LDFLAGS)  # Лінкуємо Google Test з нашою програмою

Stack.o: Stack.c
	$(CC) $(CFLAGS) -I/opt/homebrew/opt/googletest/include -c $< -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -I/opt/homebrew/opt/googletest/include -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run_tests: $(TARGET)
	./$(TARGET)