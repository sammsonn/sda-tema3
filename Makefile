CC=gcc
DEPS=tema3.c functions.c
EXE=tema3

build: $(DEPS)
	touch $(EXE).out
	$(CC) -std=c99 -Wall $^ -o $(EXE) -g

run:
	./$(EXE)

.PHONY: clean

clean:
	rm -f $(EXE)