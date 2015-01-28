#ifndef BINDRECEIVER_H
#define BINDRECEIVER_H

#include "Pdu.h"
#include "TypeOfNumber.h"
#include "NumericPlanIndicator.h"
#include <string>

namespace SMPP
{
    class BindReceiver : public Pdu
    {
    public:
        static const value_t SYSTEM_ID_MAX_LEN;
        static const value_t PASSWORD_MAX_LEN;
        static const value_t SYSTEM_TYPE_MAX_LEN;
        static const value_t ADDRESS_RANGE_MAX_LEN;

        BindReceiver();
        BindReceiver(const BindReceiver& rhs);
        BindReceiver& operator=(const BindReceiver& rhs);
        ~BindReceiver();

        const std::string& SystemId() const;
        void SetSystemId(const std::string& system_id);

        const std::string& Password() const;
        void SetPassword(const std::string& password);

        const std::string& SystemType() const;
        void SetSystemType(const std::string& system_type);

        uint32_t InterfaceVersion() const;
        TON_VALUE AddrTon() const;
        NPI AddrNpi() const;
        const char* AddressRange() const;

    private:
        virtual value_t MinBodySize() const;
        virtual value_t MaxBodySize() const;

        class BindReceiverBody;
        BindReceiverBody* body_;
    };
}

#endif // BINDRECEIVER_H
