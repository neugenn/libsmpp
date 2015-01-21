#ifndef BINDRECEIVER_H
#define BINDRECEIVER_H

#include "Pdu.h"
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

        const std::string& SystemId() const;
        void SetSystemId(const std::string& system_id);

        const std::string& Password() const;
        void SetPassword(const std::string& password);

        const std::string& SystemType() const;
        void SetSystemType(const std::string& system_type);

        uint32_t InterfaceVersion() const;
        uint8_t AddrTon() const;
        uint8_t AddrNpi() const;
        const char* AddressRange() const;
        virtual const unsigned char* Data() const;
        virtual value_t Size() const;


    private:
        virtual value_t GetMinSize() const;
        virtual value_t GetMaxSize() const;
        virtual void GetFormattedContent(std::string& s) const;

    private:
        class BindReceiverBody;
        BindReceiverBody* body_;
    };
}

#endif // BINDRECEIVER_H
