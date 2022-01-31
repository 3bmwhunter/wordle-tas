PROGRAM=wordle-analysis.out
OBJECTS=Utilities.o WordleAnalysis.o Main.o
DEPENDFILE=.depend
CC=g++
CFLAGS=-Wall -pedantic -std=c++2a


.PHONY: all

all: dep $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PROGRAM)

%.o : %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: dep

dep: *.cpp
	gcc -MM *.cpp > $(DEPENDFILE)

-include $(DEPENDFILE)

.PHONY: clean

clean:
	rm *.o
	rm *.out
