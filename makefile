FLAGS = -g -I. -In-arios -Ibinarios -INodeMetaData
OUTPUT = build
TARGET = main.cpp

all: compile

compile:
	g++ $(FLAGS) -o $(OUTPUT) $(TARGET)

run: compile
	./$(OUTPUT) < input.txt
