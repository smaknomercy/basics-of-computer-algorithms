CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET_DYNAMIC = main_dynamic
TARGET_STATIC = main_static
LIB_DIR = ./lib  # The folder containing the library
LIBS_DYNAMIC = -L$(LIB_DIR) -lstatistical_measures_dynamic -lm
LIBS_STATIC = -L$(LIB_DIR) -lstatistical_measures_static -lm

all: $(TARGET_DYNAMIC) $(TARGET_STATIC)

# For dynamic binary
$(TARGET_DYNAMIC): main.o
	$(CC) $(CFLAGS) -o $(TARGET_DYNAMIC) main.o $(LIBS_DYNAMIC) -Wl,-rpath,@executable_path/$(LIB_DIR)

# For static binary
$(TARGET_STATIC): main.o
	$(CC) $(CFLAGS) -o $(TARGET_STATIC) main.o $(LIBS_STATIC)

# Compile the main.o from the main.c
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(TARGET_DYNAMIC) $(TARGET_STATIC) main.o