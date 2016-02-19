ifeq ("$(origin V)", "undefined")
V := 0
endif

# run function
# $1: name
# $2: cmd
ifeq ($V,0)

define run
  @printf "\t%-16s%s\n" "$1" "$@"
  @$2
endef

else

define run
  $2
endef

endif
