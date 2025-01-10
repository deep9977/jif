CC = gcc
CFLAGS = -g -Wall -Wextra
TARGET = jif

all: jif

jif: main.o fileio.o transform.o bfexec.o
	$(CC) main.o fileio.o transform.o bfexec.o -o $(TARGET)

main.o: src/main.c
	$(CC) -c src/main.c $(CFLAGS) 

fileio.o: src/fileio.c
	$(CC) -c src/fileio.c $(CFLAGS) 

transform.o: src/transform.c
	$(CC) -c src/transform.c $(CFLAGS) 

bfexec.o: src/bfexec.c
	$(CC) -c src/bfexec.c $(CFLAGS) 

clean:
	rm main.o fileio.o transform.o bfexec.o $(TARGET)