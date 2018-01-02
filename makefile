6nimmt: main.o function.o
	gcc -o 6nimmt main.o function.o
main.o: main.c header.h
	gcc -c main.c
function.o: function.c header.h
	gcc -c function.c
