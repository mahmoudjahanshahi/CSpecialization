CFLAGS=-Wall -Werror -std=gnu99 -pedantic -ggdb3 -O3
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))
PROGRAM=poker

$(PROGRAM): $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	gcc -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~

cards.o: cards.h
deck.o: deck.h
eval.o: eval.h
future.o: future.h
input.o: input.h
poker.o: cards.h
poker.o: deck.h
poker.o: eval.h
poker.o: future.h
poker.o: input.h
