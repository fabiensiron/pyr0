CC		=gcc-5.3.0
RM		=rm
LIB		=include/
LDFLAGS		=-nostdlib -m32 -Wl,--build-id=none -L $(LIB)
CFLAGS		=-Wall -Wextra -nostdinc -fno-builtin -g3 -gdwarf-2 -m32 -I $(LIB)
CFLAGS		+=-fno-stack-protector -std=c99
LDSCRIPT	=boot/atomos.lds
MAKE 		=make
QEMU		=qemu-system-i386
SUBDIRS 	=boot init kernel # drivers mm fs lib
OBJS		=boot/crt0.o 			\
		boot/early_log.o 		\
		boot/cpu.o 			\
		boot/early_pagination.o 	\
		boot/setup.o 			\
		kernel/sys_call.o		\
		kernel/traps.o 			\
		init/main.o # kernel/kernel.o mm/mm.o lib/lib.a

all: atomos.img

subdirs:
	set -e
	for i in $(SUBDIRS); do $(MAKE) -C $$i || exit 1; done

atomos.img: subdirs
	$(CC) $(OBJS) -o $@ $(LDFLAGS) -T $(LDSCRIPT)

.PHONY: boot
boot: atomos.img
	$(QEMU) -kernel $^

.PHONY: debug
debug: atomos.img
	$(QEMU) -kernel $^ -s -S

.PHONY: clean
clean:
	for i in $(SUBDIRS); do $(MAKE) -C $$i $@ || exit 1; done

mrproper: clean
	$(RM) -rf atomos.img	

distclean: mrproper
