#!/usr/bin/make -f
# The -I . is for the bracket inclusion of Assert.h;
# TestSuite.h assumes Assert.h is external.
#
# Assert is my own library;
# TestSuite is my own framework that depends on Assert.
# I include them here for lab submission purposes.

CC = g++
OPTIONS = -std=c++0x -pthread -I . -Wall -g
OUTPUT = lab01
OBJECTS = Driver.o Lab01.o Lab01TestSuite.o

all: $(OBJECTS)
	$(CC) $(OPTIONS) -o $(OUTPUT) $(OBJECTS)

Driver.o: Driver.cpp Lab01TestSuite.h
	$(CC) $(OPTIONS) -c Driver.cpp

Lab01.o: Lab01.cpp Lab01.h
	$(CC) $(OPTIONS) -c Lab01.cpp

Lab01TestSuite.o: Lab01TestSuite.cpp Lab01TestSuite.h Lab01.h
	$(CC) $(OPTIONS) -c Lab01TestSuite.cpp

clean:
	rm -rf *~ *.swp *.gch $(OBJECTS) $(OUTPUT)
