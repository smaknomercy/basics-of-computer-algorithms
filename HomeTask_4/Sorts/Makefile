CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = sorting_test

all: $(TARGET)

$(TARGET): main.o sorting.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o sorting.o

main.o: main.c sorting.h
	$(CC) $(CFLAGS) -c main.c

sorting.o: sorting.c sorting.h
	$(CC) $(CFLAGS) -c sorting.c

clean:
	rm -f $(TARGET) *.o