export src_dir = '$(CURDIR)/src'
export test_dir = '$(CURDIR)/test'
PREFIX = ./stage

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
	cp $(src_dir)/dataType/PduDataType.h $(PREFIX)/include
	cp $(src_dir)/pdu/CommandId.h $(PREFIX)/include
	cp $(src_dir)/pdu/CommandStatus.h $(PREFIX)/include
	cp $(src_dir)/pdu/PduHeader.h $(PREFIX)/include
	cp $(src_dir)/pdu/Pdu.h $(PREFIX)/include
	cp $(src_dir)/pdu/BindTransmitter.h $(PREFIX)/include
	cp $(src_dir)/libsmpp.dll $(PREFIX)/lib

PHONY: all clean check
