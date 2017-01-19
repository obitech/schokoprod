# Makefile for schokoprod
# I'll include this in git since it's my first makefile and it should serve as reference

CC=c++
CFLAGS=-c -Wall

all: schokoprod

schokoprod: schokoprod_main.o schokoprod_structs.o schokoprod_functions.o
	$(CC) schokoprod_main.o schokoprod_structs.o schokoprod_functions.o -o schokoprod

schokoprod_main.o: schokoprod_main.cpp
	$(CC) $(CFLAGS) schokoprod_main.cpp

schokoprod_structs.o: schokoprod_structs.cpp
	$(CC) $(CFLAGS) schokoprod_structs.cpp

schokoprod_functions.o: schokoprod_functions.cpp
	$(CC) $(CFLAGS) schokoprod_functions.cpp

clean:
	rm *o schokoprod