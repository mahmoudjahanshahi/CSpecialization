CFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu99 -c

power: power.o test-power.o
	gcc -o power -ggdb3 power.o test-power.o
power.o: power.c power.h
	gcc $(CFLAGS) power.c
test-power.o: test-power.c power.h
	gcc $(CFLAGS) test-power.c
clean:
	rm power *.o *~

