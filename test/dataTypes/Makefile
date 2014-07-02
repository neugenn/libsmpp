src_dir = ../../src
dataType_src = $(src_dir)/dataType
test_app = test
objects =  OneByteIntegerTests.o TwoByteIntegerTests.o FourByteIntegerTests.o OctetStringTests.o \
	COctetStringTests.o AsciiValidationTests.o DecimalValidationTests.o HexValidationTests.o main.o

include $(src_dir)/SmppLibMakefile

CXXFLAGS += $(DEBUG) -Wall -I$(dataType_src)

all check: $(test_app)
	./$(test_app)

$(test_app): LFLAGS = -L$(src_dir) -l$(SMPP) -L/usr/local/lib -l cppunit
$(test_app): $(SMPPLIB) $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o $(test_app) $(LFLAGS)


OneByteIntegerTests.o: OneByteIntegerTests.cpp

TwoByteIntegerTests.o: TwoByteIntegerTests.cpp

FourByteIntegerTests.o: FourByteIntegerTests.cpp

OctetStringTests.o: OctetStringTests.cpp

COctetStringTests.o: COctetStringTests.cpp

AsciiValidationTests.o: AsciiValidationTests.cpp

DecimalValidationTests.o: DecimalValidationTests.cpp

HexValidationTests.o: HexValidationTests.cpp

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
