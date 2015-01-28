#include "DeliverSmResp.h"
#include "COctetString.h"
#include "Parameters.h"

namespace SMPP
{
    class DeliverSmResp::DeliverSmRespBody
    {
    public:
        DeliverSmRespBody() : messageId_("message_id")
        {}

        CString messageId_;
    };

    DeliverSmResp::DeliverSmResp() : Pdu("BIND_RECEIVER_RESP"), body_(NULL)
    {
        body_ = new DeliverSmRespBody;
        SetCommandId(SMPP::DELIVER_SM_RESP);

        parameters_->Add(body_->messageId_);
    }

    DeliverSmResp& DeliverSmResp::operator =(const DeliverSmResp& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        Pdu::operator =(rhs);
        *body_ = *(rhs.body_);
        parameters_->Add(body_->messageId_);

        return *this;
    }

    DeliverSmResp::DeliverSmResp(const DeliverSmResp &rhs) : Pdu(rhs), body_(NULL)
    {
        body_ = new DeliverSmRespBody(*(rhs.body_));
        parameters_->Add(body_->messageId_);
    }

    DeliverSmResp::~DeliverSmResp()
    {
        if (NULL != body_)
        {
            delete body_;
        }
    }

    value_t DeliverSmResp::MinBodySize() const
    {
        return body_->messageId_.Size();
    }

    value_t DeliverSmResp::MaxBodySize() const
    {
        return MinBodySize();

    }
}
