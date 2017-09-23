# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
# $Id$

all: package
rebuild: clean package

bootloader:
	@$(MAKE) -w -C xplbee/bootloaders

clean:
	@$(MAKE) -w -C xplbee/bootloaders $(MAKECMDGOALS)

distclean:
	@$(MAKE) -w -C xplbee/bootloaders $(MAKECMDGOALS)
	@rm -f package_epsilonrt_xplbee_index.json
	@rm -f xplbee.tar.gz

version: xplbee.tar.gz
	$(eval VERSION_TINY=$(shell git-version -t))
	$(eval VERSION=$(VERSION_TINY).$(shell git-version -p))
	@echo Package Version: $(VERSION)

hash: xplbee.tar.gz
	$(eval HASH=$(shell openssl dgst -sha256 $< | sed -e 's/.* //'))
	@echo Package Hash256: $(HASH)

size: xplbee.tar.gz
	$(eval SIZE=$(shell stat -c %s $<))
	@echo Package Size: $(SIZE) bytes

xplbee.tar.gz: bootloader
	@tar czf $@  xplbee

tar: xplbee.tar.gz

package_epsilonrt_xplbee_index.json: package_epsilonrt_xplbee_index.json.in version hash size 
	@sed -e 's/@HASH@/$(HASH)/' -e 's/@VERSION@/$(VERSION)/' -e 's/@VERSION_TINY@/$(VERSION_TINY)/' -e 's/@SIZE@/$(SIZE)/' $< > $@

package: package_epsilonrt_xplbee_index.json
	@echo  "\n\nYou should install '$<' and 'xplbee.tar.gz' in the release space: https://github.com/epsilonrt/xplbee/releases/tag/v$(VERSION)"

.PHONY: all clean distclean rebuild tar version hash size package
