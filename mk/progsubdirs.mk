$(PROG)_OBJS	+= $(addprefix $(CUR_DIR),$(OBJS))

include $Omk/deps.mk

SUBDIRS		:= $(PROGSUBDIRS)

include $Omk/subdirs.mk
