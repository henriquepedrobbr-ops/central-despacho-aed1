CC = gcc
CFLAGS = -Wall -Wextra
OBJ = main.o instalacoes.o chamados.o equipes.o historico.o

all: central

central: $(OBJ)
	$(CC) $(CFLAGS) -o central $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o central
	