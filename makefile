CC=gcc
CFLAGS=-I/src/include

sqlDocExtractor: src/main.c
	$(CC) $(CFLAGS) src/include/custom-types.c src/main.c -o dist/sqlDocExtractor
