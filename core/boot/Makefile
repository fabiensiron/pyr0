CUR_DIR		:= core/boot/

OBJS		:= 	cpu.o 			\
			crt0.o 			\
			early_pagination.o	\
			setup.o
PROGSUBDIRS	:=

include $Omk/progsubdirs.mk

pyr0_LDFLAGS	:= $(pyr0_LDFLAGS) -Wl,-T$O$(CUR_DIR)/pyr0.lds

# pyr0: $O$(CUR_DIR)pyr0.lds
