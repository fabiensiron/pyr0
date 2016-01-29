CC		=gcc-5.3.0
RM		=rm
CFLAGS		=-Wall -Wextra -nostdinc -fno-builtin -g3 -gdwarf-2 -m32 -I ../include/
CFLAGS		+=-fno-stack-protector -std=c99
ASM		=crt0.S
SRC		=cpu.c early_pagination.c setup.c early_log.c
OBJS		= $(ASM:.S=.o) $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS)

.PHONY:clean
clean:
	$(RM) *.o

.PHONY:distclean
distclean: clean

