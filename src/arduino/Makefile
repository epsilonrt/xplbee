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
	@rm -f xplee.tar.gz

version: xplee.tar.gz
	$(eval VERSION=$(shell git-version -t))
	@echo Package Version: $(VERSION)

hash: xplee.tar.gz
	$(eval HASH=$(shell openssl dgst -sha256 $< | sed -e 's/.* //'))
	@echo Package Hash256: $(HASH)

size: xplee.tar.gz
	$(eval SIZE=$(shell stat -c %s $<))
	@echo Package Size: $(SIZE) bytes

xplee.tar.gz: bootloader
	@tar czf $@  xplbee

tar: xplee.tar.gz

package_epsilonrt_xplbee_index.json: package_epsilonrt_xplbee_index.json.in version hash size 
	@sed -e 's/@HASH@/$(HASH)/' -e 's/@VERSION@/$(VERSION)/' -e 's/@SIZE@/$(SIZE)/' $< > $@

package: package_epsilonrt_xplbee_index.json
	@echo  "\n\nYou should install '$<' and 'xplee.tar.gz' in the release space: https://github.com/epsilonrt/xplbee/releases/tag/v$(VERSION)"

.PHONY: all clean distclean rebuild tar version hash size package
