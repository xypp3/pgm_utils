CC=gcc
CCFLAGS=-g -std=c99 -Wall -Wextra -lm
TARGETS=pgmEcho pgmComp pgmb2a pgma2b pgmReduce pgmTile pgmAssemble
UTILITY=pgmError.o pgmUtility.o
UTILITY_HEADERS=pgmError.h pgmUtility.h
# main executables
all: $(TARGETS)

clean:
	# store error in clean_error.txt
	rm $(TARGETS) *.o 2> clean_error.txt 

#linking process
pgmEcho:	pgmEcho.o $(UTILITY)
	# everything after .c is linked
	$(CC) $(CCFLAGS) -o pgmEcho pgmEcho.o $(UTILITY) 
pgmComp:	pgmComp.o $(UTILITY)
	# everything after .c is linked
	$(CC) $(CCFLAGS) -o pgmComp pgmComp.o $(UTILITY) 

pgmb2a:	pgmb2a.o $(UTILITY)
	# everything after .c is linked
	$(CC) $(CCFLAGS) -o pgmb2a pgmb2a.o $(UTILITY) 

pgma2b:	pgma2b.o $(UTILITY)
	# everything after .c is linked
	$(CC) $(CCFLAGS) -o pgma2b pgma2b.o $(UTILITY) 

pgmReduce:	pgmReduce.o $(UTILITY)
	# everything after .c is linked
	$(CC) $(CCFLAGS) -o pgmReduce pgmReduce.o $(UTILITY)

pgmTile:	pgmTile.o $(UTILITY)
	# everything after .c is linked
	$(CC) $(CCFLAGS) -o pgmTile pgmTile.o $(UTILITY) 

pgmAssemble:	pgmAssemble.o $(UTILITY)
	# everything after .c is linked
	$(CC) $(CCFLAGS) -o pgmAssemble pgmAssemble.o $(UTILITY) 

# compiling process WITHOUT linking
pgmEcho.o:	pgmEcho.c  $(UTILITY_HEADERS) 
	$(CC) -c $(CCFLAGS) -o pgmEcho.o pgmEcho.c 
# -c to link them together later

pgmComp.o:	pgmComp.c  $(UTILITY_HEADERS) 
	$(CC) -c $(CCFLAGS) -o pgmComp.o pgmComp.c 
# -c to link them together later

pgmb2a.o:	pgmb2a.c  $(UTILITY_HEADERS) 
	$(CC) -c $(CCFLAGS) -o pgmb2a.o pgmb2a.c 


pgma2b.o:	pgma2b.c  $(UTILITY_HEADERS) 
	$(CC) -c $(CCFLAGS) -o pgma2b.o pgma2b.c 

pgmReduce.o:	pgmReduce.c  $(UTILITY_HEADERS) 
	$(CC) -c $(CCFLAGS) -o pgmReduce.o pgmReduce.c

pgmTile.o:	pgmTile.c  $(UTILITY_HEADERS) 
	$(CC) -c $(CCFLAGS) -o pgmTile.o pgmTile.c

pgmAssemble.o:	pgmAssemble.c  $(UTILITY_HEADERS) 
	$(CC) -c $(CCFLAGS) -o pgmAssemble.o pgmAssemble.c 


## utility compiling
pgmError.o:	pgmError.c pgmError.h
	$(CC) -c $(CCFLAGS) -o pgmError.o pgmError.c

pgmUtility.o:	pgmUtility.c pgmUtility.h
	$(CC) -c $(CCFLAGS) -o pgmUtility.o pgmUtility.c
