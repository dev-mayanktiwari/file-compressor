CC = gcc
CFLAGS = -Wall -Wextra -g

#DIRECTORY
SRC_DIR = src/app
INC_DIR = src/include
OBJ_DIR = build/obj
BIN_DIR = build/bin

#SOURCE AND OBJECT FILES
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#FINAL EXECUTABLE
TARGET = $(BIN_DIR)/app

#MAKE SURE THE BUILD DIRECTORY EXISTS
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

#DEFAULT TARGET
all: $(TARGET)

#LINKING
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

#COMPILING
$$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

#CLEANING
clean:
	rm -rf $(OBJ_DIR)/* $(TARGET)

#PHONY
.PHONY: all clean