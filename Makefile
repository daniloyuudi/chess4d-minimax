HEADERS = definitions.h matrix.h move.h tree.h piece.h minimax.h math.h
OBJECTS = main.o matrix.o move.o tree.o piece.o minimax.o math.o
PROGRAM = minimax

default: $(PROGRAM)

%.o: %.c $(HEADERS)
	gcc -fPIC -c $< -o $@ \
		-I"C:\lua-5.4.2-Win64-dllw6_lib\include"

$(PROGRAM): $(OBJECTS)
	gcc $(OBJECTS) -shared -o $@ \
		-L"C:\lua-5.4.2-Win64-dllw6_lib" \
		-llua54

clean:
	del $(OBJECTS)
	del $(PROGRAM)