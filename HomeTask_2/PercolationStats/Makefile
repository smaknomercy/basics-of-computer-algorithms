# Використовуємо clang замість gcc на MacOS
CC = clang
CFLAGS = -Wall -Wextra -std=c99 -g -O2

# У разі використання архітектури ARM (M1/M2/M3 чіпи)
ARCH_FLAGS = -arch arm64

# Додаємо шлях до директорії src/dynamic_connectivity для пошуку заголовкових файлів
INCLUDE_DIRS = -Isrc
OBJ_DIR = obj
LIB_DIR = lib

LIB_PERCOLATION = $(LIB_DIR)/libpercolation.a
LIB_STATISTICAL_MEASURES = $(LIB_DIR)/libstatistical_measures.a

OBJ_PERCOLATION = $(OBJ_DIR)/percolation.o
OBJ_STATISTICAL_MEASURES = $(OBJ_DIR)/statistical_measures.o
OBJ_STATS = $(OBJ_DIR)/PercolationStats.o
OBJ_DYNAMIC_CONNECTIVITY = $(OBJ_DIR)/dynamic_connectivity.o

EXEC = percolation_simulation

OBJECTS = $(OBJ_PERCOLATION) $(OBJ_STATISTICAL_MEASURES) $(OBJ_STATS) $(OBJ_DYNAMIC_CONNECTIVITY)

# За замовчуванням компілюємо все
all: $(EXEC)

# Правило для створення виконуваного файлу
$(EXEC): $(OBJECTS) $(LIB_PERCOLATION) $(LIB_STATISTICAL_MEASURES)
	$(CC) $(CFLAGS) $(ARCH_FLAGS) $(OBJECTS) -o $(EXEC)

# Правило для створення бібліотеки libpercolation.a
$(LIB_PERCOLATION): $(OBJ_PERCOLATION)
	ar rcs $@ $^

# Правило для створення бібліотеки libstatistical_measures.a
$(LIB_STATISTICAL_MEASURES): $(OBJ_STATISTICAL_MEASURES)
	ar rcs $@ $^

# Правила для компіляції окремих об'єктних файлів
$(OBJ_PERCOLATION): src/percolation/percolation.c src/percolation/percolation.h
	$(CC) $(CFLAGS) $(ARCH_FLAGS) $(INCLUDE_DIRS) -c src/percolation/percolation.c -o $(OBJ_PERCOLATION)

$(OBJ_STATISTICAL_MEASURES): src/statistical_measures/statistical_measures.c src/statistical_measures/statistical_measures.h
	$(CC) $(CFLAGS) $(ARCH_FLAGS) $(INCLUDE_DIRS) -c src/statistical_measures/statistical_measures.c -o $(OBJ_STATISTICAL_MEASURES)

$(OBJ_STATS): PercolationStats.c PercolationStats.h
	$(CC) $(CFLAGS) $(ARCH_FLAGS) $(INCLUDE_DIRS) -c PercolationStats.c -o $(OBJ_STATS)

$(OBJ_DYNAMIC_CONNECTIVITY): src/dynamic_connectivity/dynamic_connectivity.c src/dynamic_connectivity/dynamic_connectivity.h
	$(CC) $(CFLAGS) $(ARCH_FLAGS) $(INCLUDE_DIRS) -c src/dynamic_connectivity/dynamic_connectivity.c -o $(OBJ_DYNAMIC_CONNECTIVITY)

clean:
	rm -rf $(OBJ_DIR)/*.o $(LIB_DIR)/*.a $(EXEC)

.PHONY: all clean