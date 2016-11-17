# vim:ts=4:sw=4:noexpandtab
MAKEFLAGS += --no-builtin-rules

# This variable can be overwritten to show executed commands
Q ?= @

# Default output path. This is used when output (writable) directory is different
# than project directory. You shouldn't be setting it by hand, but it is used in
# external Makefiles.
O ?= .

# Load configuration
-include $(O)/.config.mk

.PHONY: all
all: $(O)/geml

ifeq ($(DEBUG),yes)
CFLAGS += -ggdb -DDEBUG
endif
CFLAGS += -Wall
CFLAGS += -Iinclude -include $(O)/build/config.h

# Apply CPREFIX
CC:=$(CPREFIX)$(CC)

### Source files list ###########################
SRC = geml.c \
      args_parser.c \
      io.c \
      utils.c
### End of source files list ####################

CSRC = $(patsubst %,src/%,$(filter %.c,$(SRC)))

OBJ = $(patsubst src/%.c,$(O)/build/%.o,$(CSRC))
DEP = $(patsubst src/%.c,$(O)/build/%.d,$(CSRC))

.PHONY: help
help:
	@echo "General extendable macro language make targets:"
	@echo " all|geml    - Build geml executable"
	@echo " help        - Prints this text help."
	@echo " install     - Install geml to you system"
	@echo " uninstall   - Revert install target actions on your system"
	@echo " clean       - Cleans builded files"
	@echo " distclean   - Same as clean but also removes distributed generated files"
	@echo " docs        - Build html documentation"
	@echo " serve-docs  - Start html server with documentation on localhost:8000"
	@echo " clean-docs  - Removes generated documentation"
	@echo "Some enviroment variables to be defined:"
	@echo " Q             - Define emty to show executed commands"

.PHONY: install
install: $(O)/geml
	@echo " INSTALL $(EPREFIX)/bin/geml"
	$(Q)$(INSTALL) -d $(EPREFIX)/bin
	$(Q)$(INSTALL) -m 755 $(O)/geml $(EPREFIX)/bin
	@echo " INSTALL $(EPREFIX)/share/man/man1/geml.1.gz"
	$(Q)$(INSTALL) -d $(PREFIX)/share/man/man1
	$(Q)$(INSTALL) -m 644 docs/geml.man $(PREFIX)/share/man/man1/geml.1
	$(Q)$(GZIP) -f $(PREFIX)/share/man/man1/geml.1

.PHONY: uninstall
uninstall:
	@echo " RM  $(EPREFIX)/bin/geml"
	$(Q)$(RM) $(EPREFIX)/bin/geml
	@echo " RM  $(PREFIX)/share/man/man1/geml.1.gz"
	$(Q)$(RM) $(PREFIX)/share/man/man1/geml.1.gz

# Cleaning
.PHONY: clean
clean::
	@echo " CLEAN build"
	$(Q)$(RM) -r $(O)/build
	@echo " CLEAN geml"
	$(Q)$(RM) $(O)/geml
.PHONY: distclean
distclean:: clean clean-docs
	@echo " CLEAN configuration"
	$(Q)$(RM) $(O)/.config

## Building targets ##
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

$(O)/geml: $(OBJ)
	@echo " LD    $@"
	$(Q)$(CC) $(LDFLAGS) $^ -o $@

$(OBJ): $(O)/build/%.o: src/%.c $(O)/build/config.h
	@mkdir -p "$(@D)"
	@echo " CC    $@"
	$(Q)$(CC) -c $(CFLAGS) $< -o $@

$(O)/build/config.h: $(O)/.config
	@mkdir -p "$(@D)"
	@echo " CONF  $@"
	$(Q)$(O)/configure --op-h > $@
endif

## Configuation files ##
$(O)/.config:
	$(error Please run configure script first)

$(O)/.config.mk: $(O)/.config
	@echo " CONF  $@"
	$(Q)$(O)/configure --op-makefile > $@

## Documentation targets ##
.PHONY: docs
docs: docs/parser-states.dot.png
	@echo " DOC $@"
	$(Q)$(MKDOCS) build

.PHONY: serve-docs
serve-docs: docs/parser-states.dot.png
	$(Q)$(MKDOCS) serve

.PHONY: clean-docs
clean-docs:
	@echo " CLEAN docs"
	$(Q)$(RM) docs/parser-states.dot.png
	$(Q)$(RM) -r html

docs/%.dot.png: docs/%.dot
	@echo " DOT $@"
	$(Q)$(DOT) -Tpng -O $<
