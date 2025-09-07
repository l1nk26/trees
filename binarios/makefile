# Makefile para compilar y ejecutar test.cpp

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g -I../NodeMetaData/ -I. #-Werror
TARGET = test
SRC = test.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: all BinaryTree.cpp
	$(TARGET) < input.txt

run_debug_txt: all BinaryTree.cpp
	gdb -x script.txt ./$(TARGET)

run_tests:
	$(CXX) $(CXXFLAGS) -o test testTrees.cpp
	./test

clean:
	del $(TARGET).exe 2> NUL || rm -f $(TARGET)

.PHONY: all run clean
