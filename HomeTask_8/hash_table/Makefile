CC = gcc
PATH_TO_HASH = ../hash
CFLAGS = -Wall -Wextra -O2 -g -I$(PATH_TO_HASH)

TARGET = main
TEST_TARGET = test/test_hash
INTERFACE = hash_table
#IMPL = separate_chaining_impl
IMPL = linear_probing_impl

VPATH = $(PATH_TO_HASH):test

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(TARGET) $(TEST_TARGET)

$(TARGET): main.o $(IMPL).o hash_code.o
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_TARGET): test_hash.o $(IMPL).o hash_code.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o
