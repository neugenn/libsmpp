src_dir = ../../src
dataType_src = $(src_dir)/dataType
pdu_src = $(src_dir)/pdu
test_app = test
objects = PduHeaderTests.o BindTransmitterTests.o main.o

include $(src_dir)/SmppLibMakefile

CXXFLAGS += $(DEBUG) -Wall -I$(dataType_src) -I$(pdu_src)

all check: $(test_app)
	./$(test_app)

$(test_app): LFLAGS = -L$(src_dir) -l$(SMPP) -L/usr/local/lib -l cppunit
$(test_app): $(SMPPLIB) $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o $(test_app) $(LFLAGS)

PduHeaderTests.o: PduHeaderTests.cpp

BindTransmitterTests.o: BindTransmitterTests.cpp

main.o: main.cpp


$(SMPPLIB):
	@-rm -rf $(SMPPLIB)
	cd $(src_dir) && $(MAKE)
	cp $(src_dir)/$@ .

clean:
	@-rm -rf $(objects)
	@-rm -rf $(SMPPLIB)
	@-rm -rf $(test_app)*

.PHONY: clean $(SMPPLIB)
