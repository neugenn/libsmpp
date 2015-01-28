#ifndef DELIVERSM_H
#define DELIVERSM_H

#include "Pdu.h"
#include "TypeOfNumber.h"
#include "ServiceType.h"
#include "NumericPlanIndicator.h"
#include "ProrityFlag.h"
#include "DataBuffer.h"

namespace SMPP
{
    class DeliverSm : public Pdu
    {
    private:
        static const size_t SERVICE_TYPE_MAX_LEN;

    public:
        static const size_t SOURCE_ADDR_MAX_LEN;
        static const size_t DESTINATION_ADDR_MAX_LEN;

        DeliverSm();
        DeliverSm(const DeliverSm& rhs);
        DeliverSm& operator=(const DeliverSm& rhs);
        ~DeliverSm();

        void SetServiceType(SERVICE_TYPE type);
        SERVICE_TYPE ServiceType() const;

        void SetSourceAddrTon(TON_VALUE value);
        TON_VALUE SourceAddrTon() const;

        void SetSourceAddrNpi(NPI value);
        NPI SourceAddrNpi() const;

        void SetSourceAddr(const std::string& address);
        const std::string& SourceAddr() const;

        void SetDestAddrTon(TON_VALUE value);
        TON_VALUE DestAddrTon() const;

        void SetDestAddrNpi(NPI value);
        NPI DestAddrNpi() const;

        void SetDestinationAddr(const std::string& address);
        const std::string& DestinationAddr() const;

        //TODO : esm_class

        void SetProtocolId(uint8_t pid);
        uint8_t ProtocolId() const;

        void SetPriorityFlag(PRIORITY value);
        PRIORITY PriorityFlag() const;

//        void SetRegisteredDelivery();
//        void SetDataCoding();

        uint8_t SmLength() const;

        void SetShortMessage(const DataBuffer& data);

    private:
        virtual value_t MinBodySize() const;
        virtual value_t MaxBodySize() const;

        class DeliverSmBody;
        DeliverSmBody* body_;
    };
}

#endif // DELIVERSM_H
