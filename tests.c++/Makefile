CFLAGS=-O2 -std=c++1y -Wall -Werror -pthread -fconstexpr-backtrace-limit=0  -fconstexpr-depth=10000
#CFLAGS=-O -g -std=c++1y -Wall -Werror -pthread -fconstexpr-backtrace-limit=0 -fconstexpr-depth=10000
LIBS=

SRCS = $(wildcard *.cc)
PROGS = $(patsubst %.cc,%,$(SRCS))

all: $(PROGS)

clean:
	rm -rf $(PROGS) *.dSYM

%: %.cc
	$(CXX) $(CFLAGS)  -o $@ $< $(LIBS)
