# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
# $Id: Makefile 17 2013-01-28 20:53:18Z pjean $

SUBDIRS = msl usbkey
 
.PHONY: all clean distclean rebuild lib cleanlib extcoff program debug elf hex eep lss sym $(SUBDIRS)
 
$(SUBDIRS):
	$(MAKE) -w -C $@ $(MAKECMDGOALS)

all: $(SUBDIRS)
clean: $(SUBDIRS)
rebuild: $(SUBDIRS)
lib: $(SUBDIRS)
cleanlib: $(SUBDIRS)
extcoff: $(SUBDIRS)
program: $(SUBDIRS)
debug: $(SUBDIRS)

elf: $(SUBDIRS)
hex: $(SUBDIRS)
eep: $(SUBDIRS)
lss: $(SUBDIRS)
sym: $(SUBDIRS)
