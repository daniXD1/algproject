# Compiler and tools
CC = gcc
RM = rm

# Flags
CFLAGS = -Wall -O0 -fPIC
LDFLAGS = -shared

# Source and object files
SOURCES = $(wildcard *.c alg/*.c)
OBJECTS = $(SOURCES:.c=.o)

# Output shared library
TARGET = lib.so

.PHONY: all
all: $(TARGET)

# Build object files with -fPIC
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into shared library
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^
	rm $(OBJECTS)

.PHONY: clean
clean:
	-@$(RM) -f *.o alg/*.o $(TARGET)