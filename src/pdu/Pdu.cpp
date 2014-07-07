#include "Pdu.h"
#include "PduHeader.h"
#include <string.h>
#include <stdexcept>

namespace SMPP
{
    value_t Pdu::MaxSequenceNumber()
    {
        return 0x7FFFFFFF;
    }

    Pdu::Pdu() : PduDataType(), header_(new PduHeader)
    {}

    Pdu::Pdu(const unsigned char *data) : header_(new PduHeader(data))
    {}

    Pdu::Pdu(const Pdu& rsh) : PduDataType(rsh), header_(NULL)
    {
        const unsigned char* data = rsh.Data();
        header_ = new PduHeader(data);
    }

    Pdu& Pdu::operator =(const Pdu& rsh)
    {
        if (this != &rsh)
        {
            PduDataType::operator=(rsh);
            *header_ = *(rsh.header_);
        }

        return *this;
    }

    Pdu::~Pdu()
    {
        if (NULL != header_)
        {
            delete header_;
        }
    }

    value_t Pdu::CommandLength() const
    {
        return header_->CommandLength();
    }

    SMPP::CommandId Pdu::CommandId() const
    {
        return header_->CommandId();
    }

    SMPP::CommandStatus Pdu::CommandStatus() const
    {
        return header_->CommandStatus();
    }

    void Pdu::SetCommandStatus(SMPP::CommandStatus status)
    {
        return header_->SetCommandStatus(status);
    }

    value_t Pdu::SequenceNumber() const
    {
        return header_->SequenceNumber();
    }

    void Pdu::SetSequenceNumber(value_t value)
    {
        if (value > Pdu::MaxSequenceNumber())
        {
            throw std::invalid_argument("Sequence number overflow !");
        }

        header_->SetSequenceNumber(value);
    }

    void Pdu::UpdateCommandLength()
    {
        header_->SetCommandLength(this->Size());
    }

    void Pdu::SetHeader(const PduHeader& h)
    {
        *header_ = h;
    }

    bool Pdu::IsValid() const
    {
        bool res = false;
        do
        {
            if (!this->IsValidHeader())
            {
                break;
            }

            const size_t pduSize = this->Size();
            if (pduSize < this->MinSize())
            {
                break;
            }

            if (pduSize > this->MaxSize())
            {
                break;
            }

            res = this->IsValidBody();
        }
        while (false);
        return res;
    }

    void Pdu::GetFormattedContent(std::string& s) const
    {
        header_->GetFormattedContent(s);
    }

    void Pdu::GetBody(std::vector<const PduDataType *> & /*elements*/) const
    {

    }

    bool Pdu::IsValidHeader() const
    {
        return true;
    }

    bool Pdu::IsValidBody() const
    {
        std::vector<const PduDataType*> elements_;
        this->GetBody(elements_);

        std::vector<const PduDataType*>::const_iterator it = elements_.begin();
        std::vector<const PduDataType*>::const_iterator itEnd = elements_.end();
        bool res = true;
        for (; it != itEnd; ++it)
        {
            if (!(*it)->IsValid())
            {
                res = false;
                break;
            }
        }

        return res;
    }
}

std::ostream& operator<<(std::ostream& s, const SMPP::Pdu& pdu)
{
    std::string data;
    pdu.GetFormattedContent(data);

    s << data;

    return s;
}

bool operator ==(const SMPP::Pdu& lsh, const SMPP::Pdu& rsh)
{
    return ( (lsh.Size() == rsh.Size()) && (0 == memcmp(lsh.Data(), rsh.Data(), lsh.Size())) );
}

bool operator !=(const SMPP::Pdu& lsh, const SMPP::Pdu& rsh)
{
    return ( !(lsh == rsh) );
}
