
all: sizewrite sizeread

sizewrite: sizewrite.c Makefile
	$(CC) -g -O $< -o $@

sizeread: sizeread.c Makefile
	$(CC) -g -O $< -o $@
