#include "BindReceiver.h"
#include "COctetString.h"
#include "Integer.h"
#include "Parameters.h"
#include <cassert>

namespace SMPP
{
    const value_t BindReceiver::SYSTEM_ID_MAX_LEN = 16; //bytes
    const value_t BindReceiver::PASSWORD_MAX_LEN = 9; //bytes
    const value_t BindReceiver::SYSTEM_TYPE_MAX_LEN = 13; //bytes
    const value_t BindReceiver::ADDRESS_RANGE_MAX_LEN = 41; //bytes

    class BindReceiver::BindReceiverBody
    {
    public:
        BindReceiverBody() :
            systemId_("system_id"),
            password_("password"),
            systemType_("system_type"),
            interfaceVersion_("interface_version", 0x22),
            addrTon_("addr_ton"),
            addrNpi_("addr_npi"),
            addressRange_("address_range")
        {}

        BindReceiverBody(const BindReceiverBody& rhs) :
            systemId_(rhs.systemId_),
            password_(rhs.password_),
            systemType_(rhs.systemType_),
            interfaceVersion_(rhs.interfaceVersion_),
            addrTon_(rhs.addrTon_),
            addrNpi_(rhs.addrNpi_),
            addressRange_(rhs.addressRange_)
        {}

        BindReceiverBody& operator=(const BindReceiverBody& rhs)
        {
            if (this == &rhs)
            {
                return *this;
            }

            systemId_ = rhs.systemId_;
            password_ = rhs.password_;
            systemType_ = rhs.systemType_;
            interfaceVersion_ = rhs.interfaceVersion_;
            addrTon_ = rhs.addrTon_;
            addrNpi_ = rhs.addrNpi_;
            addressRange_ = rhs.addressRange_;

            return *this;
        }

        CString systemId_;
        CString password_;
        CString systemType_;
        OneByteInteger interfaceVersion_;
        OneByteInteger addrTon_;
        OneByteInteger addrNpi_;
        CString addressRange_;
    };

    BindReceiver::BindReceiver() : Pdu("BIND_RECEIVER"), body_(NULL)
    {
        body_ = new BindReceiverBody;
        SetCommandId(SMPP::BIND_RECEIVER);

        parameters_->Add(body_->systemId_);
        parameters_->Add(body_->password_);
        parameters_->Add(body_->systemType_);
        parameters_->Add(body_->interfaceVersion_);
        parameters_->Add(body_->addrTon_);
        parameters_->Add(body_->addrNpi_);
        parameters_->Add(body_->addressRange_);
    }

    BindReceiver::BindReceiver(const BindReceiver &rhs) : Pdu(rhs), body_(NULL)
    {
        body_ = new BindReceiverBody(*(rhs.body_));

        parameters_->Add(body_->systemId_);
        parameters_->Add(body_->password_);
        parameters_->Add(body_->systemType_);
        parameters_->Add(body_->interfaceVersion_);
        parameters_->Add(body_->addrTon_);
        parameters_->Add(body_->addrNpi_);
        parameters_->Add(body_->addressRange_);
    }

    BindReceiver& BindReceiver::operator=(const BindReceiver &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        Pdu::operator =(rhs);
        *body_ = *(rhs.body_);

        parameters_->Add(body_->systemId_);
        parameters_->Add(body_->password_);
        parameters_->Add(body_->systemType_);
        parameters_->Add(body_->interfaceVersion_);
        parameters_->Add(body_->addrTon_);
        parameters_->Add(body_->addrNpi_);
        parameters_->Add(body_->addressRange_);

        return *this;
    }

    BindReceiver::~BindReceiver()
    {
        if (NULL != body_)
        {
            delete body_;
            body_ = NULL;
        }
    }

    const std::string &BindReceiver::SystemId() const
    {
        return body_->systemId_.Value();
    }

    void BindReceiver::SetSystemId(const std::string &system_id)
    {
        if (system_id.size() > SYSTEM_ID_MAX_LEN)
        {
            throw int(10);
        }

        body_->systemId_.SetValue(system_id);
    }

    const std::string &BindReceiver::Password() const
    {
        return body_->password_.Value();
    }

    void BindReceiver::SetPassword(const std::string &password)
    {
        if (password.size() > PASSWORD_MAX_LEN)
        {
            throw int(10);
        }

        body_->password_.SetValue(password);
    }

    const std::string &BindReceiver::SystemType() const
    {
        return body_->systemType_.Value();
    }

    void BindReceiver::SetSystemType(const std::string &system_type)
    {
        if (system_type.size() > SYSTEM_TYPE_MAX_LEN)
        {
            throw int(10);
        }

        body_->systemType_.SetValue(system_type);
    }

    uint32_t BindReceiver::InterfaceVersion() const
    {
        return body_->interfaceVersion_.Value();
    }

    uint8_t BindReceiver::AddrTon() const
    {
        return body_->addrTon_.Value();
    }

    uint8_t BindReceiver::AddrNpi() const
    {
        return body_->addrNpi_.Value();
    }

    const char* BindReceiver::AddressRange() const
    {
        return body_->addressRange_.Value().c_str();
    }

    value_t BindReceiver::MinBodySize() const
    {
        return 4 * CString().Size() + 3 * OneByteInteger().Size();
    }

    value_t BindReceiver::MaxBodySize() const
    {
        return SYSTEM_ID_MAX_LEN + PASSWORD_MAX_LEN + SYSTEM_TYPE_MAX_LEN + \
                3 * OneByteInteger().Size() + ADDRESS_RANGE_MAX_LEN;
    }
}
