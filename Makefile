# vim:ts=4:sw=4:noexpandtab
MAKEFLAGS += --no-builtin-rules

# Load configuration
-include $(O)/.config.mk

# Default output path. Can be changed by enviroment to compile to different folder
# than default.
O ?= .
# This variable can be overwritten to show executed commands
Q = @

# TODO add CROSS_COMPILE support
BISON ?= bison
CC ?= gcc
# TODO also other tools


.PHONY: all
all: $(O)/sgp

# TODO modules

ifeq ($(DEBUG),yes)
CFLAGS += -ggdb -DDEBUG
endif
CFLAGS += -Wall
CFLAGS += -Iinclude -include $(O)/build/config.h

### Source files list ###########################
SRC = sgp.c \
	  utils.c \
	  parser.c \
	  io.c \
	  command.c
### End of source files list ####################

CSRC = $(patsubst %,src/%,$(filter %.c,$(SRC)))
YSRC = $(patsubst %,src/%,$(filter %.y,$(SRC)))
CYSRC = $(patsubst %,%.c,$(YSRC))
HYSRC = $(patsubst %,%.h,$(YSRC))
CSRC += $(CYSRC)
GPERFSRC = $(patsubst %,src/%,$(filter %.gperf,$(SRC)))
HGPERFSRC = $(patsubst %,%.h,$(GPERFSRC))

OBJ = $(patsubst src/%.c,$(O)/build/%.o,$(CSRC))
DEP = $(patsubst src/%.c,$(O)/build/%.d,$(CSRC))

.PHONY: help
help:
	@echo "Simple general preprocessor make targets:"
	@echo " all|sgp     - Build sgp executable"
	@echo " help        - Prints this text help."
	@echo " install     - Install sgp to you system"
	@echo " uninstall   - Revert install target actions on your system"
	@echo " clean       - Cleans builded files"
	@echo " distclean   - Same as clean but also removes distributed generated files"
	@echo " docs        - Build html documentation"
	@echo " serve-docs  - Start html server with documentation on localhost:4000"
	@echo " clean-docs  - Removes generated documentation"
	@echo "Some enviroment variables to be defined:"
	@echo " CROSS_COMPILE - Specifies installation prefix. Default is /usr/local"
	@echo " Q             - Define emty to show executed commands"

.PHONY: install
install:
	#TODO

.PHONY: uninstall
uninstall:
	#TODO

# Cleaning
.PHONY: clean
clean::
	@echo " CLEAN build"
	$(Q)$(RM) -r $(O)/build
	@echo " CLEAN sgp"
	$(Q)$(RM) $(O)/sgp
.PHONY: distclean
distclean:: clean
	@echo " CLEAN distributed"
	$(Q)$(RM) $(CYSRC)
	$(Q)$(RM) $(HYSRC)
	$(Q)$(RM) $(HGPERFSRC)
	@echo " CLEAN configuration"
	$(Q)$(RM) $(O)/.config

.PHONY: docs
docs:
	@echo " DOC $@"
	$(Q)mkdocs build

.PHONY: serve-docs
serve-docs:
	$(Q)mkdocs serve

.PHONY: clean-docs
clean-docs:
	@echo " CLEAN docs"
	$(Q)$(RM) -r site

ifeq (,$(filter clean distclean help docs serve-docs clean-docs \
	  ,$(MAKECMDGOALS))) # Ignore build targets if goal is not building
ifeq ($(DEBUG),yes)
-include $(DEP) # If developing, use dependencies from source files
.PHONY: dependency dep
dependency dep:: $(DEP)
$(DEP): $(O)/build/%.d: src/%.c
	@mkdir -p "$(@D)"
	@echo " DEP   $@"
	$(Q)$(CC) -MM -MG -MT '$*.o $@' $(CFLAGS) $< -MF $@
endif # DEBUG

$(O)/sgp: $(OBJ)
	@echo " LD    $@"
	$(Q)$(CC) $(CFLAGS) $^ -o $@

$(OBJ): $(O)/build/%.o: src/%.c $(O)/build/config.h
	@mkdir -p "$(@D)"
	@echo " CC    $@"
	$(Q)$(CC) -c $(CFLAGS) $< -o $@

$(O)/build/config.h: $(O)/.config
	@mkdir -p "$(@D)"
	@echo " CONF  $@"
	$(Q)./configure --op-h > $@

$(HGPERFSRC): %.y.h: %.y.c
	@
$(CYSRC): %.y.c: %.y
	@echo " BISON $@"
	$(Q)$(BISON) -d -o $@ $<

$(HGPERFSRC): %.h: %
	@echo " GPERF $@"
	$(Q)$(GPERF) --output-file=$@ $<
endif

# Configuation files
$(O)/.config:
	$(error Please run configure script first)

$(O)/.config.mk: $(O)/.config
	@echo " CONF  $@"
	$(Q)./configure --op-makefile > $@
