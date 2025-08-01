# Simple Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -march=native
LDFLAGS = -lm
TARGET = test
SRCDIR = .
OBJDIR = obj
BINDIR = bin

# Source files
SOURCES = $(SRCDIR)/test.c
OBJECTS = $(OBJDIR)/test.o

# Default target
all: dirs $(BINDIR)/$(TARGET)

# Create directories
dirs:
	mkdir -p $(OBJDIR) $(BINDIR)

# Build the executable
$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Rebuild everything
rebuild: clean all

.PHONY: all dirs clean rebuild
