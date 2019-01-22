################################
##
## PLATOTerm For X68000 Makefile
##
################################

CC=gcc
CFLAGS=-O0

LIBS=-liocs -ldos

OBJS=	screen.o	\
	protocol.o	\
	terminal.o	\
	io.o		\
	keyboard.o	\
	touch.o		\
	config.o	\
	main.o

all:	plato.x

clean:
	rm -f *.o *~
	rm -f dos/*

plato.x:	$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) \
	-o plato.x $(LIBS)

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@
