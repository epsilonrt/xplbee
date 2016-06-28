###############################################################################
# Copyright © 2016 epsilonRT, All rights reserved.                            #
# This software is governed by the CeCILL license <http://www.cecill.info>    #
###############################################################################
#SUBDIRS = bootloader demo
CLEANER_SUBDIRS = test

all: $(SUBDIRS)
clean: $(SUBDIRS) $(CLEANER_SUBDIRS)
distclean: $(SUBDIRS) $(CLEANER_SUBDIRS) 
rebuild: $(SUBDIRS)


$(SUBDIRS):
	$(MAKE) -w -C $@ $(MAKECMDGOALS)

$(CLEANER_SUBDIRS):
	$(MAKE) -w -C $@ $(MAKECMDGOALS)
	

.PHONY: all clean distclean rebuild $(SUBDIRS) $(CLEANER_SUBDIRS)

