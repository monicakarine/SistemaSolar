CC=gcc
OPCOES_COMPILADOR=-I.-ISOIL -lglut -lGLU -lSOIL -lGLEW -lGL -w -lm `sdl-config --cflags --libs` -ISDL -lSDL_mixer
TODOS_ARQUIVOS_PONTOH = include.h textura.h sistema.h carregaobj.h
TODOS_ARQUIVOS_OBJ = main.o textura.o sistema.o carregaobj.c

%.o: ../%.c $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	gcc -o main $^ $(OPCOES_COMPILADOR)

run: all
	./main

clean:
	rm *.o main
