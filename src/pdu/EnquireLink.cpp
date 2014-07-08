#include "EnquireLink.h"
#include "PduHeader.h"


namespace SMPP
{
    EnquireLink::EnquireLink() : Pdu()
    {}

    EnquireLink::EnquireLink(const PduHeader& h) :
    Pdu(h)
    {
    }

    const unsigned char* EnquireLink::Data() const
    {
        return header_.Data();
    }

    value_t EnquireLink::Size() const
    {
        return header_.Size();
    }

    value_t EnquireLink::GetMinSize() const
    {
        return this->Size();
    }

    value_t EnquireLink::GetMaxSize() const
    {
        return this->GetMinSize();
    }
}
