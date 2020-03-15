HEADDERS = audit.h backup.h lockper.h logit.h track.h transfer.h unlockper.h 

default: daemon

daemon.o: daemon.c $(HEADDERS)
	gcc -c daemon.c -o daemon.o

daemon: daemon.o
	gcc daemon.o -o webd

clean:
	-rm -f daemon.o