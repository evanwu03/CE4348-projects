CC = gcc

CFLAGS   = -Wall -g -I/include

# Production sources (C)
SRC_SRCS  = src/*.c

# Objects
SRC_OBJS  = $(SRC_SRCS:../src/%.c=build/%.o)

OBJS = $(SRC_OBJS)
TARGET_NAME = project1
TARGET = build/$(TARGET_NAME)

.PHONY: all clean run

all: $(TARGET)

# Link final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# Compile .cpp into build/
build/%.o: %.cpp | build
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Compile .c into build/
build/%.o: ../src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build dir exists
build:
	mkdir -p build

# Clean build directory
clean:
	rm -rf build

run: 
	make all && cd build/ && ./$(TARGET_NAME)

