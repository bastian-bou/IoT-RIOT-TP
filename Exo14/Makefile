APPLICATION=BaseSys_rename

BOARD ?= native

# we want to use SAUL:
USEMODULE += saul_default

USEMODULE += tsl2561

CFLAGS += -DTSL2561_PARAM_ADDR=TSL2561_ADDR_LOW

USEMODULE += shell

USEMODULE += shell_commands

USEMODULE += ps

RIOTBASE ?= $(CURDIR)/../../RIOT

DEVELHELP ?= 1

include $(RIOTBASE)/Makefile.include


