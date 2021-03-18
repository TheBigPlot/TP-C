CC=gcc
CFLAGS=-Wall -Wextra  -g
LDFLAGS=-ldl

SRC = $(wildcard\
alloc.c \
structs.c \
basics/*.c \
lists/*.c \
queues/*.c \
graphs/*.c \
.tests/.*.c \
.tests/.res/.*.c \
.tests/.unitTest/.*.c \
)
DEPS = $(SRC:.c=.h)
OBJ = $(SRC:.c=.o)


MYSRC = $(wildcard\
MyMain.c \
structs.c \
basics/*.c \
lists/*.c \
queues/*.c \
graphs/*.c \
)
MYDEPS=$(MYSRC:.c=.h)
MYOBJ=$(MYSRC:.c=.h) 

my_tests: $(MYOBJ)
	$(CC) -o my_tests $^ $(LDFLAGS)

my_clean:
	rm $(MYOBJ)
	rm my_tests

tests: $(OBJ)
	$(CC) -o  tests $^ $(LDFLAGS)

clean:
	rm $(OBJ)
	rm tests


