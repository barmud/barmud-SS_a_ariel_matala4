C =gcc
AR = ar
FLAGS = -Wall -g

all: graph

graph: main.c edges.c nodes.c
	$(C) $(FLAGS) main.c edges.c nodes.c -o graph
	
clean:rm -rf *.o graph

.phony: clean,all 