CC = g++
LFLAGS = -o PA9
CFLAGS = -Wall -O3 -c#-O2 -c

PA9 : WStem.o main.o PCwords.o basic.o Doc.o
	$(CC) main.o WStem.o PCwords.o basic.o Doc.o -Wall -g -I. $(LFLAGS)

main.o : main.cpp WStem.h PCwords.h basic.h Doc.h
	$(CC) main.cpp -g -I. $(CFLAGS)

Doc.o : Doc.cpp Doc.h
	$(CC) Doc.cpp -g -I. $(CFLAGS)

WStem.o : WStem.cpp WStem.h
	$(CC) WStem.cpp -g -I. $(CFLAGS)

PCwords.o : PCwords.cpp PCwords.h
	$(CC) PCwords.cpp -g -I. $(CFLAGS)

basic.o : basic.cpp basic.h Doc.h
	$(CC) basic.cpp -g -I. $(CFLAGS)

clean :
	-rm *.o PA9

sub : clean
	cd ..; tar -cvf PA9.tar PA9/main.cpp PA9/WStem.cpp PA9/WStem.h PA9/basic.cpp PA9/basic.h PA9/PCwords.cpp PA9/PCwords.h PA9/Doc.cpp PA9/Doc.h PA9/Makefile
