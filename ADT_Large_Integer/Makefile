# Compiler and flags
CC = g++
CFLAGS = -fPIC -w -O3 -o
LDFLAGS = 
SFLAGS = -shared 


# Target executable
TARGET = count_pairs

# Source files
SRCS = count_pairs.cpp  # Include main.c if it exists

# Object files
OBJS = $(SRCS:.c=.c)

# Python script to run
PYTHON_SCRIPT = hw1.py
FILENAME = inputs.txt

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

# Compile C source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up build files
clean:
	rm -f liblargeinteger.so 
	rm -f $(TARGET)

# Run the Python script after building
run: all
	$(CC) $(SFLAGS) $(CFLAGS) liblargeinteger.so count_pairs.cpp
	python3 $(PYTHON_SCRIPT) $(FILENAME)

.PHONY: all clean run