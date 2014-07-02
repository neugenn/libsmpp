export src_dir = '$(CURDIR)/src'
export test_dir = '$(CURDIR)/test'

all:	
	cd $(src_dir) && $(MAKE) $@

clean:
	cd $(src_dir) && $(MAKE) $@
	cd $(test_dir) && $(MAKE) $@

check:
	cd $(test_dir) && $(MAKE) $@

PHONY: all clean check
