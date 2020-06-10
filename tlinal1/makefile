linal: main.o func.o
	gcc -lm main.o func.o -o linal

main.o: main.c func.c defs.h
	gcc -c main.c func.c

clean: main.o linal
	rm main.o func.o linal

