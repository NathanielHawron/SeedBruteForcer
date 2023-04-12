OBJECT := .o/cli.o
ARGS :=


.o/%.o: src/%.cpp
	g++ $^ -c -o $@ -I include


compile: $(OBJECT)
	g++ src/main.cpp -o main.exe $(OBJECT) -I include

run: compile
	./main.exe $(ARGS)
