FLAGS = -g -I. -In-arios -Ibinarios -INodeMetaData
OUTPUT = build
TARGET = main.cpp

all: compile

compile:
	g++ $(FLAGS) -o $(OUTPUT) $(TARGET)

run: compile
	./$(OUTPUT) < input.txt

clean:
	rm -rf $(OUTPUT)

all_tests:
	@for test in tests/TreeN/*; do name=$$(echo $$test | cut -f 1 -d "." | cut -f 3 -d "/"); g++ $(FLAGS) -o ./$(OUTPUT) $$test; echo -n "$$name: "; ./$(OUTPUT) && echo "All tests passed" || "Tests failed"; done

