src=$(wildcard *.c)
obj=$(src:.c=.o)

CC=gcc
CFLAGS=-std=c99 -Wall -D_REENTRANT -I. -I/usr/local/lib -g
LDFLAGS=


generateBind: $(obj)
		$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) generateBind
