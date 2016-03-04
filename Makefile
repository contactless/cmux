
CC?=gcc
CFLAGS?=-Wall -std=gnu99 -g

DESTDIR?=/
PREFIX?=usr

TARGETS=cmux client

all: cmux client

% : %.c
	$(CC) $(CFLAGS) $< -o $@

install: cmux
	install -m 0755 cmux $(DESTDIR)/$(PREFIX)/bin/cmux

clean:
	-@rm -vf $(TARGETS) 

.PHONY: install clean
