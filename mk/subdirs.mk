SUBDIRS		:= $(addprefix $(CUR_DIR),$(SUBDIRS))
$(foreach D,$(SUBDIRS),$(shell mkdir -p $D))

include $(addsuffix Makefile,$(addprefix $O,$(SUBDIRS)))
