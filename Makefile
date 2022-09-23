CFLAGS=	-O2 -Wall -Werror -Wextra -pedantic -ansi

all: turnstile

.c.o:
	${CC} ${CFLAGS} -c $<

turnstile: turnstile.o
	${CC} -o $@ $?

clean:
	rm -rf *.o *.core turnstile

.PHONY: all clean
