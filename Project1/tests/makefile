CC = g++
CPPUTEST_HOME = /usr/share/cpputest

CFLAGS   = -Wall -g -I../include
CPPFLAGS = -I$(CPPUTEST_HOME)/include 
LDLIBS   = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

# Test sources (C++)
TEST_SRCS = AllTests.cpp MemoryTests.cpp
# Production sources (C)
SRC_SRCS  = ../src/memory.c ../src/disk.c 

# Objects
TEST_OBJS = $(TEST_SRCS:%.cpp=build/%.o)
SRC_OBJS  = $(SRC_SRCS:../src/%.c=build/%.o)

OBJS = $(TEST_OBJS) $(SRC_OBJS)
TARGET = build/AllTests

.PHONY: all clean

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
