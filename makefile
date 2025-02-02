SRC_DIR       = src
OBJ_DIR       = obj
BIN_DIR       = bin
INCLUDE_DIR   = $(SRC_DIR)

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/train.c \
       $(SRC_DIR)/file_ops.c \
       $(SRC_DIR)/material.c \
       $(SRC_DIR)/wagon.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/box.c
	 
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET = train_management

CC = gcc
CFLAGS = -Wall -g -I$(INCLUDE_DIR)

all: make_directories $(BIN_DIR)/$(TARGET)

make_directories:
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"

$(BIN_DIR)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(BIN_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if exist "$(OBJ_DIR)" rmdir /s /q "$(OBJ_DIR)"
	@if exist "$(BIN_DIR)" rmdir /s /q "$(BIN_DIR)"

run: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET)
