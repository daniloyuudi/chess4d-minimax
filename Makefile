HEADERS = definitions.h matrix.h move.h tree.h piece.h
OBJECTS = main.o matrix.o move.o tree.o piece.o

default: program

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

program: $(OBJECTS)
	gcc $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f program