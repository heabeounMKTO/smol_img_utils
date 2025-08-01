# Compiler and flags
CC = gcc
CFLAGS_DEBUG = -g -Wall -O0
CFLAGS_RELEASE = -O3 -Wall -DNDEBUG

# File and directory setup
SRC = main.c test.c common_img_utils.c
OBJ_DEBUG = $(addprefix build/debug_, $(SRC:.c=.o))
OBJ_RELEASE = $(addprefix build/release_, $(SRC:.c=.o))
BIN_DIR = bin
BUILD_DIR = build

# Output binaries
OUT_DEBUG = $(BIN_DIR)/main_debug
OUT_RELEASE = $(BIN_DIR)/main_release

.PHONY: all debug release clean

all: build

build: release

debug: $(OUT_DEBUG)

release: $(OUT_RELEASE)

# Compile debug
$(OUT_DEBUG): $(OBJ_DEBUG)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_DEBUG) -o $@

build/debug_%.o: %.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS_DEBUG) -c $< -o $@

# Compile release
$(OUT_RELEASE): $(OBJ_RELEASE)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_RELEASE) -o $@

build/release_%.o: %.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS_RELEASE) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

