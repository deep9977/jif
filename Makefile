CC = gcc
TARGET = jif

all: jif

jif: main.o transform.o bfexec.o
	$(CC) main.o transform.o bfexec.o -o $(TARGET)

main.o: src/main.c
	$(CC) -c src/main.c

transform.o: src/transform.c
	$(CC) -c src/transform.c 

bfexec.o: src/bfexec.c
	$(CC) -c src/bfexec.c

clean:
	rm main.o transform.o bfexec.o $(TARGET)