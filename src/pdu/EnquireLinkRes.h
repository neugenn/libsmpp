#ifndef ENQUIRELINKRES_H
#define ENQUIRELINKRES_H

#include "Pdu.h"

namespace SMPP
{
    class EnquireLinkRes : public Pdu
    {
    public:
        EnquireLinkRes();
        EnquireLinkRes(const PduHeader& h);

        virtual const unsigned char* Data() const;
        virtual value_t Size() const;

    private:
        virtual value_t MinBodySize() const;
        virtual value_t MaxBodySize() const;
    };
}

#endif // ENQUIRELINK_H
