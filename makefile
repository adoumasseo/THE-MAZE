# Variables
CC = gcc
CFLAGS = -Werror -Wall -Wextra -pedantic
LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_mixer -lm
SRCDIR = ./src
SRC = $(wildcard $(SRCDIR)/*.c)
TARGET = raycaster

# Default target
all: $(TARGET)

# Build the project
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Run the project
run:
	./$(TARGET)

# Clean up generated files
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean run
