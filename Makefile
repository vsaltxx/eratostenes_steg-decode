CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra

all: primes primes-i steg-decode

primes: primes.o error.o bitset.o eratosthenes.o
	$(CC) $(CFLAGS) primes.o error.o bitset.o eratosthenes.o -o primes

primes-i: primes-i.o error.o bitset-i.o eratosthenes-i.o bitset.o
	$(CC) $(CFLAGS) -DUSE_INLINE primes-i.o error.o bitset-i.o eratosthenes-i.o -o primes-i

steg-decode: steg-decode.o ppm.o error.o bitset.o eratosthenes.o
	$(CC) $(CFLAGS) steg-decode.o ppm.o error.o bitset.o eratosthenes.o -o steg-decode

primes.o: primes.c primes.h bitset.h error.h eratosthenes.h
	$(CC) $(CFLAGS) -c primes.c -o primes.o

primes-i.o: primes.c bitset.c primes.h bitset.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c primes.c -o primes-i.o

ppm.o: ppm.c ppm.h error.h
	$(CC) $(CFLAGS) -c ppm.c -o ppm.o

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

bitset.o: bitset.c bitset.h
	$(CC) $(CFLAGS) -c bitset.c -o bitset.o

bitset-i.o: bitset.c bitset.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c bitset.c -o bitset-i.o

eratosthenes.o: eratosthenes.c bitset.h eratosthenes.h
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes.o

eratosthenes-i.o: eratosthenes.c bitset.h eratosthenes.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c eratosthenes.c -o eratosthenes-i.o

clean:
	rm -f *.o primes primes-i steg-decode

run: all
	time ./primes
	time ./primes-i



