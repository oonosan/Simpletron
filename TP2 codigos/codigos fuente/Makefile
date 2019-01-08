CC=gcc
CFLAGS=-ansi -Wall -pedantic
OBJECTS=main.o argumentos.o dump.o errores.o lectores.o listas.o simpletron.o vectores.o

tp: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o simpletron
	
main.o: main.c comun.h tipos.h vectores.h listas.h argumentos.h errores.h simpletron.h lectores.h dump.h
	$(CC) -c main.c
argumentos.o: argumentos.c argumentos.h tipos.h
	$(CC) -c argumentos.c
dump.o: dump.c dump.h simpletron.h
	$(CC) -c dump.c
errores.o: errores.c tipos.h errores.h
	$(CC) -c errores.c
lectores.o: lectores.c tipos.h lectores.h argumentos.h vectores.h comun.h simpletron.h
	$(CC) -c lectores.c
listas.o: listas.c listas.h tipos.h	
	$(CC) -c listas.c
simpletron.o: simpletron.c tipos.h simpletron.h comun.h
	$(CC) -c simpletron.c
vectores.o: vectores.c vectores.h tipos.h
	$(CC) -c vectores.c
clean:
	rm -f *.o tp