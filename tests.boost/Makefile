CXXFLAGS=-O2 -std=c++11 -Wall -Werror  -fconstexpr-depth=9300 -pthread
LIBS= -lboost_system-mt -lboost_log-mt -lboost_log-mt

SRCS = $(wildcard *.cpp)
PROGS = $(patsubst %.cpp,%,$(SRCS))

all: $(PROGS)

clean:
	rm $(PROGS)

%: %.cpp
	$(CXX) $(CXXFLAGS)  -o $@ $< $(LIBS)
