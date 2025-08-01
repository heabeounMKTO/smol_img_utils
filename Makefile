# Project configuration
PROJECT_NAME = image_processor
SOURCES = main.c test.c
HEADERS = stb_image.h std_image_write.h common_img_utils.h

# Compiler and flags
CC = gcc
CFLAGS_DEBUG = -Wall -Wextra -std=c99 -g -O0 -DDEBUG
CFLAGS_RELEASE = -Wall -Wextra -std=c99 -O3 -DNDEBUG
CFLAGS_TEST = -Wall -Wextra -std=c99 -O0 -DTEST

# Directories
BUILD_DIR = build
DEBUG_DIR = $(BUILD_DIR)/debug
RELEASE_DIR = $(BUILD_DIR)/release
TEST_DIR = $(BUILD_DIR)/test

# Object files
OBJECTS_DEBUG = $(SOURCES:.c=.o)
OBJECTS_RELEASE = $(SOURCES:.c=.o)
OBJECTS_TEST = $(SOURCES:.c=.o)

# Targets
.PHONY: all debug release test clean install uninstall help

# Default target
all: debug

# Debug build
debug: $(DEBUG_DIR)/$(PROJECT_NAME)
	@echo "Debug build complete: $@"

$(DEBUG_DIR)/$(PROJECT_NAME): $(addprefix $(DEBUG_DIR)/, $(OBJECTS_DEBUG))
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(CFLAGS_DEBUG) -o $@ $^

$(DEBUG_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(CFLAGS_DEBUG) -c $< -o $@

# Release build
release: $(RELEASE_DIR)/$(PROJECT_NAME)
	@echo "Release build complete: $@"

$(RELEASE_DIR)/$(PROJECT_NAME): $(addprefix $(RELEASE_DIR)/, $(OBJECTS_RELEASE))
	@mkdir -p $(RELEASE_DIR)
	$(CC) $(CFLAGS_RELEASE) -o $@ $^

$(RELEASE_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(RELEASE_DIR)
	$(CC) $(CFLAGS_RELEASE) -c $< -o $@

# Test build
test: $(TEST_DIR)/$(PROJECT_NAME)
	@echo "Test build complete: $@"

$(TEST_DIR)/$(PROJECT_NAME): $(addprefix $(TEST_DIR)/, $(OBJECTS_TEST))
	@mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS_TEST) -o $@ $^

$(TEST_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS_TEST) -c $< -o $@

# Clean all builds
clean:
	rm -rf $(BUILD_DIR)

# Install (copy to system directory)
install: release
	@echo "Installing to /usr/local/bin/$(PROJECT_NAME)"
	cp $(RELEASE_DIR)/$(PROJECT_NAME) /usr/local/bin/$(PROJECT_NAME)

# Uninstall
uninstall:
	@echo "Removing /usr/local/bin/$(PROJECT_NAME)"
	rm -f /usr/local/bin/$(PROJECT_NAME)

# Help
help:
	@echo "Available targets:"
	@echo "  all      - Build debug version (default)"
	@echo "  debug    - Build debug version"
	@echo "  release  - Build release version"
	@echo "  test     - Build test version"
	@echo "  clean    - Remove all build files"
	@echo "  install  - Install release version"
	@echo "  uninstall- Remove installed version"
	@echo "  help     - Show this help"

# Run debug version
run: debug
	./$(DEBUG_DIR)/$(PROJECT_NAME)

# Run release version
run-release: release
	./$(RELEASE_DIR)/$(PROJECT_NAME)

# Run test version
run-test: test
	./$(TEST_DIR)/$(PROJECT_NAME)
