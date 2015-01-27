dataType_src = dataType
optional_src = $(dataType_src)/optional
pdu_src = pdu
#objects = PduDataType.o Integer.o OctetString.o COctetString.o AsciiValidation.o DecimalValidation.o \
          HexValidation.o PduHeader.o Pdu.o BindTransmitter.o BindTransmitterResp.o EnquireLink.o EnquireLinkRes.o BindReceiver.o DataBuffer.o
 
objects = PduDataType.o Integer.o OctetString.o COctetString.o AsciiValidation.o DecimalValidation.o \
          HexValidation.o Pdu.o BindReceiver.o BindReceiverResp.o DataBuffer.o Parameters.o 
#Tlv.o 
#ScInterfaceVersion.o

CXXFLAGS += $(DEBUG) -c -Wall -fpic 
VPATH = $(dataType_src):$(pdu_src):$(optional_src)

include SmppLibMakefile

all: $(SMPPLIB)

$(SMPPLIB): $(objects)
	$(CXX) $(DEBUG) -shared -o $@ $(objects)

PduDataType.o: PduDataType.cpp
	$(CXX) $(CXXFLAGS) $^

OctetString.o: OctetString.cpp
	$(CXX) $(CXXFLAGS) $^

Integer.o: Integer.cpp
	$(CXX) $(CXXFLAGS) $^

COctetString.o: COctetString.cpp
	$(CXX) $(CXXFLAGS) $^

AsciiValidation.o: AsciiValidation.cpp
	$(CXX) $(CXXFLAGS) $^

DecimalValidation.o: DecimalValidation.cpp
	$(CXX) $(CXXFLAGS) $^

HexValidation.o: HexValidation.cpp
	$(CXX) $(CXXFLAGS) $^

CXXFLAGS += -I$(dataType_src)
PduHeader.o: PduHeader.cpp
	$(CXX) $(CXXFLAGS) $^

Pdu.o: Pdu.cpp
	$(CXX) $(CXXFLAGS) $^

BindTransmitter.o: BindTransmitter.cpp
	$(CXX) $(CXXFLAGS) $^

BindTransmitterResp.o: BindTransmitterResp.cpp
	$(CXX) $(CXXFLAGS) $^

EnquireLink.o: EnquireLink.cpp
	$(CXX) $(CXXFLAGS) $^

EnquireLinkRes.o: EnquireLinkRes.cpp
	$(CXX) $(CXXFLAGS) $^

BindReceiver.o: BindReceiver.cpp
	$(CXX) $(CXXFLAGS) $^

CXXFLAGS += -I$(optional_src)
BindReceiverResp.o: BindReceiverResp.cpp
	$(CXX) $(CXXFLAGS) $^

DataBuffer.o: DataBuffer.cpp
	$(CXX) $(CXXFLAGS) $^

Parameters.o: Parameters.cpp
	$(CXX) $(CXXFLAGS) $^

CXXFLAGS += -I$(pdu_src)
Tlv.o: Tlv.cpp
	$(CXX) $(CXXFLAGS) $^

ScInterfaceVersion.o: ScInterfaceVersion.cpp
	$(CXX) $(CXXFLAGS) $^

clean:
	@-rm -f $(SMPPLIB)
	@-rm -f $(objects)

