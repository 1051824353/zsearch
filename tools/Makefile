include ../compile.mk
CFLAG = -Wall -g -I./ 

LIB = 

SRC = $(wildcard ./*.c)
OBJ = $(patsubst %.c,%.o,$(SRC))

BIN = tools.a

all: base
base:
	make clean;make $(BIN)

$(BIN):$(OBJ)
	$(AR) r $@ $(OBJ) 


%.o:%.c
	$(CC2) $(CFLAG) $(LIB) -c $< -o $@
%.o:%.cpp
	$(CC2) $(CFLAG) $(LIB) -c $< -o $@

cl:
	make clean

clean:
	rm -rf $(OBJ) $(BIN) 


