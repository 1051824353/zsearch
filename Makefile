include ./compile.mk

CFLAG = -Wall -g  -D$(ARCH)

CURDIR = $(shell pwd)

OS = $(shell getconf LONG_BIT)

INCLUDE = -I./ -I./tools/

OBJS = zsearch.o tools/tools.a 
SERVER = zsearch 

all:
	make $(SERVER)


$(SERVER):$(OBJS)
	$(CC2) $(CFLAG) -o $@ $(INCLUDE) $(OBJS)
%.o:%.c
	$(CC2) $(CFLAG) -c $< $(INCLUDE)
tools/tools.a:
	cd tools && make

cl:
	make clean
clean:
	@rm -rf $(SERVER) *.o
	cd tools && make clean
