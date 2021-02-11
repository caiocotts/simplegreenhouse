
lab04:  lab04.o ghcontrol.o
	gcc -g -o lab04 lab04.o ghcontrol.o

lab04.o: lab04.c ghcontrol.h
	gcc -g -c lab04.c

ghcontrol.o: ghcontrol.c ghcontrol.h
	gcc -g -c ghcontrol.c

clean:
	rm -f *.o lab04 stamp.txt





