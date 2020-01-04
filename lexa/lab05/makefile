BIN_DIR = bin
INC_DIR = inc
OBJ_DIR = obj
SRC_DIR = src
TMP_DIR = tmp
APP_EXE = app

RM := rm
MKDIR := mkdir
LOG := log.txt

CC := g++
CFLAGS := -std=c++17 -I$(INC_DIR) -Wall -Werror -pedantic

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DIRS := $(OBJ_DIR) $(BIN_DIR) $(TMP_DIR)

.PHONY: all dir run clean

all: dir $(BIN_DIR)/$(APP_EXE)

run: all
	./$(BIN_DIR)/$(APP_EXE) 2>$(TMP_DIR)/$(LOG)

$(BIN_DIR)/$(APP_EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

dir: $(DIRS)

$(DIRS):
	$(MKDIR) -p $@

clean:
	$(RM) -rf $(DIRS)
