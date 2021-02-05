
main:  main.o func.o
	cc main.c func.o -o main

main.o: main.c func.h
	cc main.c -c

func.o: func.c func.h
	cc func.c -c

clean:
	rm -f *.o main serialnum
# Use clean to remove all object, exectutable, files as well
# as serialnum from your working directory
 


