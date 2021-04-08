
main:  main.o func.o pisensehat.o
	cc main.o func.o pisensehat.o -lwiringPi -o main

main.o: main.c func.h
	cc main.c -c

func.o: func.c func.h
	cc func.c -c

pisensehat.o: pisensehat.c pisensehat.h	
	cc pisensehat.c -c

clean:
	clearmatrix
	rm -f *.o main serialnum && touch *
# Use clean to remove all object, exectutable, files as well
# as serialnum from your working directory
 


