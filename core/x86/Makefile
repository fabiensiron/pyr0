CUR_DIR		:= core/x86/

OBJS		:=	bios.o			\
			cmos.o			\
			cpu.o 			\
			cpuid_check.o		\
			cpuinfo.o		\
			crt0.o 			\
			early_pagination.o	\
			irq.o			\
			isr.o			\
			kbd.o			\
			pit.o			\
			reboot.o		\
			serial.o		\
			setup.o			\
			snd.o			\
			traps.o			\
			traps_support.o		\
			video.o

PROGSUBDIRS	:=

include $Omk/progsubdirs.mk

pyr0_LDFLAGS	:= $(pyr0_LDFLAGS) -Wl,-T$O$(CUR_DIR)/pyr0.lds

# pyr0: $O$(CUR_DIR)pyr0.lds
