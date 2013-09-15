#!/usr/bin/make -f

CC = g++
OPTIONS = -std=c++0x -Wall -g
LIBRARIES = -pthread -lassert -ltestsuite 
OUTPUT = lab01
OBJECTS = Driver.o Lab01.o Lab01TestSuite.o

all: $(OBJECTS)
	$(CC) $(OPTIONS) -o $(OUTPUT) $(OBJECTS) $(LIBRARIES)

Driver.o: Driver.cpp Lab01TestSuite.h
	$(CC) $(OPTIONS) -c Driver.cpp 

Lab01.o: Lab01.cpp Lab01.h
	$(CC) $(OPTIONS) -c Lab01.cpp

Lab01TestSuite.o: Lab01TestSuite.cpp Lab01TestSuite.h Lab01.h
	$(CC) $(OPTIONS) -c Lab01TestSuite.cpp

clean:
	rm -rf *~ *.swp *.gch $(OBJECTS) $(OUTPUT)
