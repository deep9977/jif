CC = gcc
TARGET = jif

all: jif

jif: main.o transform.o
	$(CC) main.o transform.o -o $(TARGET)

main.o: src/main.c
	$(CC) -c src/main.c

transform.o: src/transform.c
	$(CC) -c src/transform.c 

clean:
	rm main.o transform.o $(TARGET)