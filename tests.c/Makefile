CFLAGS=-O2 -std=gnu99 -Wall -Werror -pthread
#LIBS=-lnanomsg
LIBS=-lm

SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

clean:
	rm $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $<
