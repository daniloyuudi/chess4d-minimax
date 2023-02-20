HEADERS = definitions.h matrix.h move.h tree.h piece.h minimax.h math.h
OBJECTS = main.o matrix.o move.o tree.o piece.o minimax.o math.o
PROGRAM = minimax.dll

default: $(PROGRAM)

%.o: %.c $(HEADERS)
	gcc -fPIC -c $< -o $@ \
		-I"C:\luajit\src"

$(PROGRAM): $(OBJECTS)
	gcc $(OBJECTS) -shared -o $@ \
		-L"C:\luajit\src" \
		-llua51

clean:
	del $(OBJECTS)
	del $(PROGRAM)