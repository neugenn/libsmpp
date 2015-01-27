export src_dir = '$(CURDIR)/src'
export test_dir = '$(CURDIR)/test'
PREFIX = ./stage

include $(smpplib)

all:	
	cd $(src_dir) && $(MAKE) $@

clean:
	cd $(src_dir) && $(MAKE) $@
	cd $(test_dir) && $(MAKE) $@

check:
	cd $(test_dir) && $(MAKE) $@

install: all
	mkdir -p $(PREFIX)/include
	mkdir -p $(PREFIX)/lib
	find $(src_dir) -name *.h -exec cp {} $(PREFIX)/include \;
	cp $(src_dir)/*.so $(PREFIX)/lib

PHONY: all clean check
