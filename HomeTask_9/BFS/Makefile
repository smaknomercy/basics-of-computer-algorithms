# Compiler and flags
CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -g

# Main program
TARGET       := lecture_11
MAIN_SRCS    := lecture_11.c graph.c paths.c dfs.c bfs.c queue.c
MAIN_OBJS    := lecture_11.o graph.o paths.o dfs.o bfs.o queue.o

# Test: Paths (DFS/BFS)
TEST_PATHS       := test_paths
TEST_PATHS_SRCS  := test/test_paths.c
TEST_PATHS_OBJS  := test_paths.o graph.o paths.o dfs.o bfs.o queue.o

# Test: BFS‐based shortest path
TEST_BFS            := test_bfs_shortest
TEST_BFS_SRCS       := test/test_bfs_shortest.c
TEST_BFS_OBJS       := test_bfs_shortest.o graph.o

.PHONY: all clean

all: $(TARGET) $(TEST_PATHS) $(TEST_BFS)

# ------------------------
# Link main program
# ------------------------
$(TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile main sources
lecture_11.o: lecture_11.c graph.h paths_helper.h
	$(CC) $(CFLAGS) -c $< -o $@

graph.o: graph.c graph.h paths_helper.h
	$(CC) $(CFLAGS) -c $< -o $@

paths.o: paths.c paths.h paths_helper.h graph.h
	$(CC) $(CFLAGS) -c $< -o $@

dfs.o: dfs.c dfs.h paths_helper.h graph.h paths.h
	$(CC) $(CFLAGS) -c $< -o $@

bfs.o: bfs.c bfs.h queue.h paths_helper.h graph.h paths.h
	$(CC) $(CFLAGS) -c $< -o $@

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------
# Link test_paths
# ------------------------
$(TEST_PATHS): $(TEST_PATHS_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

test_paths.o: test/test_paths.c dfs.h paths_helper.h paths.h bfs.h queue.h graph.h
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------
# Link test_bfs_shortest
# ------------------------
$(TEST_BFS): $(TEST_BFS_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

test_bfs_shortest.o: test/test_bfs_shortest.c graph.h
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------
# Clean up
# ------------------------
clean:
	rm -f $(TARGET) $(TEST_PATHS) $(TEST_BFS) *.o
