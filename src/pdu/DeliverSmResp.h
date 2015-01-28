#ifndef DELIVERSMRESP_H
#define DELIVERSMRESP_H

#include "Pdu.h"

namespace SMPP
{
    class DeliverSmResp : public Pdu
    {
    public:
        DeliverSmResp();
        DeliverSmResp(const DeliverSmResp& rhs);
        DeliverSmResp& operator=(const DeliverSmResp& rhs);
        ~DeliverSmResp();

    private:
        virtual value_t MinBodySize() const;
        virtual value_t MaxBodySize() const;

        class DeliverSmRespBody;
        DeliverSmRespBody* body_;
    };
}

#endif // DELIVERSMRESP_H
