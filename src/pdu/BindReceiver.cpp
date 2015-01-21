#include "BindReceiver.h"
#include "COctetString.h"
#include "Integer.h"
#include <cassert>

namespace SMPP
{
    const value_t BindReceiver::SYSTEM_ID_MAX_LEN = 16; //bytes
    const value_t BindReceiver::PASSWORD_MAX_LEN = 9; //bytes
    const value_t BindReceiver::SYSTEM_TYPE_MAX_LEN = 13; //bytes
    const value_t BindReceiver::ADDRESS_RANGE_MAX_LEN = 41; //bytes

    class BindReceiver::BindReceiverBody : public PduDataType
    {
    public:
        BindReceiverBody() : PduDataType(),
            systemId_("system_id"),
            password_("password"),
            systemType_("system_type"),
            interfaceVersion_("interface_version"),
            addrTon_("addr_ton"),
            addrNpi_("addr_npi"),
            addressRange_("address_range")
        {
        }

        virtual const unsigned char* Data() const
        {
            assert(NULL != __PRETTY_FUNCTION__);
            return NULL;

        }

        virtual value_t Size() const
        {
            return systemId_.Size() + password_.Size() \
                + systemType_.Size() + interfaceVersion_.Size() \
                + addrTon_.Size() + addrNpi_.Size() + addressRange_.Size();
        }

        CString systemId_;
        CString password_;
        CString systemType_;
        OneByteInteger interfaceVersion_;
        OneByteInteger addrTon_;
        OneByteInteger addrNpi_;
        CString addressRange_;
    };

    BindReceiver::BindReceiver() : Pdu(), body_(NULL)
    {
        header_.SetCommandId(SMPP::BIND_RECEIVER);
        header_.SetCommandLength(GetMinSize());

        body_ = new BindReceiverBody;
        parameters_.push_back(body_);

        buffer_.Alloc(GetMaxSize());
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
        static uint32_t Version(0x22); //3.4
        return Version;
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

    const unsigned char* BindReceiver::Data() const
    {
        unsigned char* data = buffer_.Data();
        memcpy(data, header_.Data(), header_.Size());
        size_t offset = header_.Size();

        memcpy(data + offset, body_->systemId_.Data(), body_->systemId_.Size());
        offset += body_->systemId_.Size();

        memcpy(data + offset, body_->password_.Data(), body_->password_.Size());
        offset += body_->password_.Size();

        memcpy(data + offset, body_->systemType_.Data(), body_->systemType_.Size());
        offset += body_->systemType_.Size();

        memcpy(data + offset, body_->interfaceVersion_.Data(), body_->interfaceVersion_.Size());
        offset += body_->interfaceVersion_.Size();

        memcpy(data + offset, body_->addrTon_.Data(), body_->addrTon_.Size());
        offset += body_->addrTon_.Size();

        memcpy(data + offset, body_->addrNpi_.Data(), body_->addrNpi_.Size());
        offset += body_->addrNpi_.Size();

        memcpy(data + offset, body_->addressRange_.Data(), body_->addressRange_.Size());

        return data;
    }

    value_t BindReceiver::Size() const
    {
        return header_.Size() + body_->Size();
    }

    value_t BindReceiver::GetMinSize() const
    {
        return PduHeader().Size() + 4 * CString().Size() + 3 * OneByteInteger().Size();
    }

    value_t BindReceiver::GetMaxSize() const
    {
        return PduHeader().Size() + SYSTEM_ID_MAX_LEN + PASSWORD_MAX_LEN + SYSTEM_TYPE_MAX_LEN + \
                3 * OneByteInteger().Size() + ADDRESS_RANGE_MAX_LEN;
    }

    void BindReceiver::GetFormattedContent(std::string &s) const
    {
        s.clear();
        Pdu::GetFormattedContent(s);

        std::stringstream str;
        str << s;
        str << body_->systemId_.Name() << " : " << body_->systemId_ << " (" << body_->systemId_.Value() << ")" << std::endl;
        str << body_->password_.Name() << " : " << body_->password_ << " (" << body_->password_.Value() << ")" << std::endl;
        str << body_->systemType_.Name() << " : " << body_->systemType_ << " (" << body_->systemType_.Value() << ")" << std::endl;
        str << body_->interfaceVersion_.Name() << " : " << body_->interfaceVersion_ << " (" << InterfaceVersion() << ")" << std::endl;
        str << body_->addrTon_.Name() << " : " << body_->addrTon_ << " (" << body_->addrTon_.Value() << ")" << std::endl;
        str << body_->addrNpi_.Name() << " : " << body_->addrNpi_ << " (" << body_->addrNpi_.Value() << ")" << std::endl;
        str << body_->addressRange_.Name() << " : " << body_->addressRange_ << " (" << body_->addressRange_.Value() << ")" << std::endl;

        s = str.str();
    }
}
