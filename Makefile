# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -g -I$(INC_DIR)

# Directory paths
SRC_DIR = src/app
INC_DIR = src/include
OBJ_DIR = build/obj
BIN_DIR = build/bin

# Source files
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/huffman.c \
       $(SRC_DIR)/compress.c \
       $(SRC_DIR)/decompress.c

# Object files (replacing .c with .o)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Final executable name
TARGET = $(BIN_DIR)/compressor

# Make sure the build directories exist
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	@echo "Linking..."
	@$(CC) $(OBJS) -o $(TARGET)
	@echo "Build complete! Binary created at $(TARGET)"

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	@echo "Cleaning build files..."
	@rm -rf $(OBJ_DIR)/* $(TARGET)
	@echo "Clean complete!"

# Run tests 
test: $(TARGET)
	@echo "Running tests..."
	@./$(TARGET) comp test.txt
	@./$(TARGET) decomp test.txt.huf
	@echo "Tests complete!"

# Phony targets
.PHONY: all clean test