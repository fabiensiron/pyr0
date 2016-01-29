CC		=gcc
RM		=rm
CFLAGS		=-Wall -Wextra -nostdinc -fno-builtin -g3 -gdwarf-2 -m32 -I ../include/
CFLAGS		+=-fno-stack-protector -std=c99
SRC		=main.c
OBJS		= $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS)

.PHONY:clean
clean:
	$(RM) *.o

.PHONY:distclean
distclean: clean

