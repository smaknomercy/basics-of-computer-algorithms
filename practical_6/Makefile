CC = gcc
CFLAGS = -Wall -g
OBJ = convex_hull.o
TARGET = convex_hull

# Default target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

convex_hull.o: convex_hull.c convex_hull.h
	$(CC) $(CFLAGS) -c convex_hull.c

clean:
	rm -f $(OBJ) $(TARGET)