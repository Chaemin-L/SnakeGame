# Makefile
CC = g++
CCFLAGS = -g

Main: Main.o Rules.o Item.o Gate.o Map.o
	$(CC) $(CCFLAGS) -o $@ $^ -lncurses

clean:
	rm -f *.o

%.o : %.cpp %.h
	$(CC) $(CCFLAGS) -c $<

%.o : %.cpp
	$(CC) $(CCFLAGS) -c $<
