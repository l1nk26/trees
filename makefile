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
	@for test in tests/TreeN/*; do name=$$(echo $$test | cut -f 1 -d "." | cut -f 3 -d "/"); echo -e -n "\033[34m$$name: \033[0m"; g++ $(FLAGS) -o ./$(OUTPUT) $$test && ./$(OUTPUT) && echo -e "\033[32mAll tests passed\033[0m" || echo -e "\033[31mTests failed\033[0m"; done

