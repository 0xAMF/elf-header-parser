# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -I./src

# Source files
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

# Main file
MAIN = main.c
MAIN_OBJ = $(MAIN:.c=.o)

# Executable
TARGET = myreadelfh

# Default rule
all: $(TARGET)

# Link objects
$(TARGET): $(MAIN_OBJ) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile main
$(MAIN_OBJ): $(MAIN)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile src/*.c
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(TARGET) $(OBJS) $(MAIN_OBJ)

.PHONY: all clean
