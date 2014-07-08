#include "EnquireLinkRes.h"
#include "PduHeader.h"

namespace SMPP
{
    EnquireLinkRes::EnquireLinkRes() : Pdu()
    {}

    EnquireLinkRes::EnquireLinkRes(const PduHeader& h) : Pdu(h)
    {}

    const unsigned char* EnquireLinkRes::Data() const
    {
        return header_.Data();
    }

    value_t EnquireLinkRes::Size() const
    {
        return header_.Size();
    }

    value_t EnquireLinkRes::GetMinSize() const
    {
        return this->Size();
    }

    value_t EnquireLinkRes::GetMaxSize() const
    {
        return this->GetMinSize();
    }
}
