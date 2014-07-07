#include "BindTransmitter.h"
#include "Integer.h"
#include "COctetString.h"
#include "PduHeader.h"

namespace SMPP
{
    const size_t BindTransmitter::SystemIdMaxLen = 16; //bytes
    const size_t BindTransmitter::PasswordMaxLen = 9; //bytes
    const size_t BindTransmitter::SystemTypeMaxLen = 13; //bytes
    const size_t BindTransmitter::AddressRangeMaxLen = 41; //bytes

    class BindTransmitter::BindTransmitterPrivate
    {
    public:
        BindTransmitterPrivate() :
        systemId_("system_id"),
        password_("password"),
        systemType_("system_type"),
        interfaceVersion_("interface_version"),
        addrTon_("addr_ton"),
        addrNpi_("addr_npi"),
        addressRange_("address_range"),
        data_(new unsigned char[MaxSize()])
        {}

        BindTransmitterPrivate(const unsigned char* data) :
        systemId_("system_id"),
        password_("password"),
        systemType_("system_type"),
        interfaceVersion_("interface_version"),
        addrTon_("addr_ton"),
        addrNpi_("addr_npi"),
        addressRange_("address_range"),
        data_(new unsigned char[MaxSize()])
        {
            systemId_ = CString(data, SystemIdMaxLen, "system_id");
            password_ = CString(data, PasswordMaxLen, "password");
            systemType_ = CString(data, SystemTypeMaxLen, "system_type");
            interfaceVersion_ = OneByteInteger(data, "interface_version");
            addrTon_ = OneByteInteger(data, "addr_ton");
            addrNpi_ = OneByteInteger(data, "addr_npi");
            addressRange_ = CString(data, AddressRangeMaxLen, "address_range");
        }

        BindTransmitterPrivate(const BindTransmitterPrivate& rsh) :
        systemId_(rsh.systemId_),
        password_(rsh.password_),
        systemType_(rsh.systemType_),
        interfaceVersion_(rsh.interfaceVersion_),
        addrTon_(rsh.addrTon_),
        addrNpi_(rsh.addrNpi_),
        addressRange_(rsh.addressRange_),
        data_(new unsigned char[MaxSize()])
        {}

        BindTransmitterPrivate& operator=(const BindTransmitterPrivate& rsh)
        {
            if (this != &rsh)
            {
                systemId_ = rsh.systemId_;
                password_ = rsh.password_;
                systemType_ = rsh.systemType_;
                interfaceVersion_ = rsh.interfaceVersion_;
                addrTon_ = rsh.addrTon_;
                addrNpi_ = rsh.addrNpi_;
                addressRange_ = rsh.addressRange_;
                memcpy(data_, rsh.data_, MaxSize());
            }

            return *this;
        }

        ~BindTransmitterPrivate()
        {
            if (NULL != data_)
            {
                delete [] data_;
            }
        }

        static size_t MinSize()
        {
            return PduHeader().Size() + 4 * CString().Size() + 3 * OneByteInteger().Size();
        }

        static size_t MaxSize()
        {
            return PduHeader().Size() + BindTransmitter::SystemIdMaxLen + BindTransmitter::PasswordMaxLen + \
            BindTransmitter::SystemTypeMaxLen + BindTransmitter::AddressRangeMaxLen + 3 * OneByteInteger().Size();
        }

        size_t Size() const
        {
                return systemId_.Size() + password_.Size() + systemType_.Size() \
                + interfaceVersion_.Size() + addrTon_.Size() + addrNpi_.Size() + addressRange_.Size();
        }

        unsigned char* Data()
        {
            bzero(data_, this->MaxSize());
            return data_;
        }

        CString systemId_;
        CString password_;
        CString systemType_;
        OneByteInteger interfaceVersion_;
        OneByteInteger addrTon_;
        OneByteInteger addrNpi_;
        CString addressRange_;
        unsigned char* data_;
    };


    BindTransmitter::BindTransmitter() :
    Pdu(),
    impl_(new BindTransmitterPrivate())
    {
        header_->SetCommandId(SMPP::BIND_TRANSMITTER);
        header_->SetCommandLength(BindTransmitterPrivate::MinSize());
    }

    BindTransmitter::BindTransmitter(const unsigned char* data, size_t len) :
    Pdu(data),
    impl_(NULL)
    {
        if (len < BindTransmitterPrivate::MinSize())
        {
            std::stringstream s;
            s << __PRETTY_FUNCTION__ << " : The size of the data buffer(" << len << ") ";
            s << "is smaller than the minimum allowed PDU size(" << BindTransmitterPrivate::MinSize() <<") !";
            throw std::invalid_argument(s.str());
        }

        impl_ = new BindTransmitterPrivate(data);
    }

    BindTransmitter::~BindTransmitter()
    {
        if (NULL != impl_)
        {
            delete impl_;
        }
    }

    BindTransmitter::BindTransmitter(const PduHeader& rsh) : Pdu(),
    impl_(new BindTransmitterPrivate)
    {
        this->SetHeader(rsh);
        header_->SetCommandLength(BindTransmitterPrivate::MinSize());
    }

    BindTransmitter::BindTransmitter(const BindTransmitter &rsh) :
    Pdu(rsh),
    impl_(new BindTransmitterPrivate(*(rsh.impl_)))
    {
    }

    BindTransmitter& BindTransmitter::operator =(const BindTransmitter &rsh)
    {
        if (this == &rsh)
        {
            return *this;
        }

        Pdu::operator=(rsh);
        *impl_ = *(rsh.impl_);
        return *this;
    }

    void BindTransmitter::GetFormattedContent(std::string &s) const
    {
        s.clear();
        Pdu::GetFormattedContent(s);

        std::stringstream str;
        str << s;
        str << "system_id: " << impl_->systemId_ << " (" << impl_->systemId_.Value() << ")" << std::endl;
        str << "password: " << impl_->password_ << " (" << impl_->password_.Value() << ")" << std::endl;
        str << "system_type: " << impl_->systemType_ << " (" << impl_->systemType_.Value() << ")" << std::endl;
        str << "interface_version: " << impl_->interfaceVersion_ << std::endl;
        str << "addr_ton: " << impl_->addrTon_ << std::endl;
        str << "addr_npi: " << impl_->addrNpi_ << std::endl;
        str << "address_range: " << impl_->addressRange_;

        s = str.str();
    }

    size_t BindTransmitter::MinSize() const
    {
        return BindTransmitterPrivate::MinSize();
    }

    size_t BindTransmitter::MaxSize() const
    {
        return BindTransmitterPrivate::MaxSize();
    }

    unsigned const char* BindTransmitter::Data() const
    {
        unsigned char* buf = impl_->Data();

        memcpy(buf, header_->Data(), header_->Size());
        size_t offset = header_->Size();

        memcpy(buf + offset, impl_->systemId_.Data(), impl_->systemId_.Size());
        offset += impl_->systemId_.Size();

        memcpy(buf + offset, impl_->password_.Data(), impl_->password_.Size());
        offset += impl_->password_.Size();

        memcpy(buf + offset, impl_->systemType_.Data(), impl_->systemType_.Size());
        offset += impl_->systemType_.Size();

        memcpy(buf + offset, impl_->interfaceVersion_.Data(), impl_->interfaceVersion_.Size());
        offset += impl_->interfaceVersion_.Size();

        memcpy(buf + offset, impl_->addrTon_.Data(), impl_->addrTon_.Size());
        offset += impl_->addrTon_.Size();

        memcpy(buf + offset, impl_->addrNpi_.Data(), impl_->addrNpi_.Size());
        offset += impl_->addrNpi_.Size();

        memcpy(buf + offset, impl_->addressRange_.Data(), impl_->addressRange_.Size());

        return buf;
    }

    size_t BindTransmitter::Size() const
    {
        return header_->Size() + impl_->Size();
    }

    void BindTransmitter::GetBody(std::vector<const PduDataType *> &elements) const
    {
        elements.clear();
        elements.push_back(&impl_->systemId_);
        elements.push_back(&impl_->password_);
        elements.push_back(&impl_->systemType_);
        elements.push_back(&impl_->interfaceVersion_);
        elements.push_back(&impl_->addrTon_);
        elements.push_back(&impl_->addrNpi_);
        elements.push_back(&impl_->addressRange_);
    }

    bool BindTransmitter::IsValidHeader() const
    {
        return false;
    }
}
