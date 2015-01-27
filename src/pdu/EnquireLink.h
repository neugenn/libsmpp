#ifndef ENQUIRELINK_H
#define ENQUIRELINK_H

#include "Pdu.h"

namespace SMPP
{
    class EnquireLink : public Pdu
    {
    public:
        EnquireLink();
        EnquireLink(const PduHeader& h);

        virtual const unsigned char* Data() const;
        virtual value_t Size() const;

    private:
        virtual value_t MinBodySize() const;
        virtual value_t MaxBodySize() const;
    };
}

#endif // ENQUIRELINK_H
