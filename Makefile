FLAGS = -Wall

SERVER = simpled
CLIENTS = ssSet

all: $(SERVER) $(CLIENTS)

csapp.h:
	wget http://csapp.cs.cmu.edu/2e/ics2/code/include/csapp.h

csapp.c:
	wget http://csapp.cs.cmu.edu/2e/ics2/code/src/csapp.c

csapp.o: csapp.h csapp.c

clients: ssSet

simpled: simpled.cpp csapp.o 
	g++ $(CFLAGS) simpled.cpp csapp.o -lpthread -o simpled

ssSet: ssSet.cpp csapp.o 
	g++ $(CFLAGS) ssSet.cpp csapp.o -lpthread -o ssSet

.PHONY: clean
clean:
	/bin/rm -rf csapp.h csapp.c *.o simpled ssSet ssGet ssDigest ssRun
