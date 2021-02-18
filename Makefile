CC_OBJECT = cc -Wall -g -DNDEBUG -c -o
CC        = cc -Wall -g -DNDEBUG

SRCS = $(wildcard *[^_main].c)
SRC  = $(wildcard *_main.c)
OBJ  = $(SRCS:%.c=%.o)
BIN  = $(SRC:%.c=%)

all: $(OBJ) $(BIN)

%.o: %.c
	$(CC_OBJECT) $@ $< 

%: %.c
	$(CC) $(SRC) $(OBJ) -o $@

clean:
	@echo "Cleaning... $(OBJ)"
	rm -f *.o
	@echo "Cleaning... $(BIN)"
	rm -f $(BIN)
	
