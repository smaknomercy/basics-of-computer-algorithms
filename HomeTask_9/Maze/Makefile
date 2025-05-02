# Makefile for maze_sdl on macOS with Homebrew SDL2 in /opt/homebrew/opt

CC       := gcc
CFLAGS   := -Wall -Wextra \
            -I. \
            -I../BFS \
            -I/opt/homebrew/opt/sdl2/include
LDFLAGS  := -L/opt/homebrew/opt/sdl2/lib -lSDL2

BFS_DIR  := ../BFS
BFS_SRCS := graph.c paths.c dfs.c bfs.c queue.c
BFS_OBJS := $(BFS_SRCS:.c=.o)

OBJS     := maze_sdl.o maze.o $(BFS_OBJS)
TARGET   := maze_sdl

.PHONY: all clean

all: $(TARGET)

# Link final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile your SDL2 maze renderer
maze_sdl.o: maze_sdl.c maze.h \
            $(BFS_DIR)/graph.h \
            $(BFS_DIR)/paths.h \
            $(BFS_DIR)/paths_helper.h \
            $(BFS_DIR)/bfs.h \
            $(BFS_DIR)/dfs.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile your maze implementation
maze.o: maze.c maze.h
	$(CC) $(CFLAGS) -c $< -o $@

# Pattern rule: compile BFS/DFS sources
%.o: $(BFS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.o
