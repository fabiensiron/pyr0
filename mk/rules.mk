COMMA	:= ,

%.o: %.c
	$(call run,CC,$(CC) $(DEFAULT_CFLAGS) $(CFLAGS) -MD -MP -c $< -o $@)

%.o: %.S
	$(call run,AS,$(CC) $(DEFAULT_ASFLAGS) $(ASFLAGS) -MD -MP -c $< -o $@)

%.ko:
	$(call run,MOD,$(CC) $(DEFAULT_LDFLAGS) $(LDFLAGS) -Wl$(COMMA)-r $^ -o $@)

%.a:
	$(call run,RM,rm -f $@)
	$(call run,AR,$(AR) csr $@ $^)
