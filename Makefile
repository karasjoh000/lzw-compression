#########################################################
#
# John Karasev
#

LZWLIB=lzwLib
TARFILE=JohnKarasevA1P2
CFLAGS=-c -g -std=c99 -Wall -pedantic -I$(LZWLIB)/include

lzw: main.o $(LZWLIB)/liblzw.a
	gcc -g -L$(LZWLIB) main.o -o lzw -llzw

main.o: main.c $(LZWLIB)/include/lzw.h
	gcc $(CFLAGS) main.c

$(LZWLIB)/liblzw.a:
	cd $(LZWLIB) && make liblzw.a

clean:
	rm -f lzw main.o $(TARFILE).tar $(TARFILE).tar.gz
	cd $(LZWLIB) && make clean

tar: clean
	tar cvf $(TARFILE).tar $(LZWLIB)
	gzip $(TARFILE).tar
