CC = gcc
CXX = g++

CFLAGS = -Wall -g -std=c11
CXXFLAGS = -Wall -g -std=c++20 -I/opt/homebrew/opt/googletest/include

LDFLAGS = -L/opt/homebrew/opt/googletest/lib
LIBS = -lgtest -lgtest_main -pthread

OBJS = BST.o node.o test_bst.o

all: test_bst

BST.o: BST.c BST.h node.h item.h
	$(CC) -c $(CFLAGS) BST.c -o BST.o

node.o: node.c node.h item.h
	$(CC) -c $(CFLAGS) node.c -o node.o

test_bst.o: test_bst.cpp BST.h node.h item.h
	$(CXX) -c $(CXXFLAGS) test_bst.cpp -o test_bst.o

test_bst: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o test_bst $(LIBS)

clean:
	rm -f *.o test_bst

.PHONY: all clean
