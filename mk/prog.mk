_PROG		:= $(addprefix $(CUR_DIR),$(PROG))

$(PROG)_OBJS	:=

include $Omk/progsubdirs.mk

$(PROG)_CFLAGS			?=
$(PROG)_ASFLAGS			?=
LIBS				?=

$(_PROG): CFLAGS		:= $($(PROG)_CFLAGS)
$(_PROG): ASFLAGS		:= $($(PROG)_ASFLAGS)

$(_PROG): $($(PROG)_OBJS) $(foreach L,$(LIBS),$($(L)_FULL_PATH).a)

$(PROG)_LDFLAGS		?=
$(_PROG)_LDFLAGS	:= $($(PROG)_LDFLAGS) $(foreach L,$(LIBS),$($(L)_LINKFLAGS))
$(_PROG)_OBJS		:= $($(PROG)_OBJS)

$(_PROG):
	$(call run,BIN,$(LD) -o $@ $($@_OBJS) $($@_LDFLAGS) $(DEFAULT_LDFLAGS))

root/$(INSTALL_DIR)/$(PROG): $(_PROG) | root/$(INSTALL_DIR)/
	$(call run,COPY,cp $< $@)
	$(call run,STRIP,$(STRIP) -s $@)

PROG_INSTALL	:= $(PROG_INSTALL) root/$(INSTALL_DIR)/$(PROG)

PROG		:= $(_PROG)

ALL_PROGS	:= $(ALL_PROGS) $(PROG)
