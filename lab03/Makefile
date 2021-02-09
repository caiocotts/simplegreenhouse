
lab03:  lab03.o ghcontrol.o
	gcc -g -o lab03 lab03.o ghcontrol.o

lab03.o: lab03.c ghcontrol.h
	gcc -g -c lab03.c

ghcontrol.o: ghcontrol.c ghcontrol.h
	gcc -g -c ghcontrol.c

clean:
	rm -f *.o lab03 stamp.txt





