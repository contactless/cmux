
CC?=gcc
CFLAGS?=-Wall -std=gnu99 -g
DESTDIR?=/
PREFIX?=usr
TARGETS=cmux test 

all: cmux client test

cmux: cmux.c
	$(CC) $(CFLAGS) cmux.c -o cmux

client: client.c
	$(CC) $(CFLAGS) client.c -o client

test: test.c
	$(CC) $(CFLAGS) test.c -o test

install: cmux
	install -m 0755 cmux $(DESTDIR)/$(PREFIX)/bin/cmux

clean:
	-@rm -vf $(TARGETS) 

.PHONY: install clean
