all: stat.o
	gcc -o work8 stat.o

stat.o: stat.c
	gcc -c stat.c

run: all
	./work8

clean:
	rm -f work8
	rm -f *~
	rm -f *.o


