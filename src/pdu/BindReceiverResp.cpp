#include "BindReceiverResp.h"
#include "COctetString.h"
#include "Integer.h"
#include "Parameters.h"
#include "Tlv.h"

namespace SMPP
{
    const value_t BindReceiverResp::SYSTEM_ID_MAX_LEN = 16; //bytes

    class BindReceiverResp::BindReceiverRespBody
    {
    public:
        BindReceiverRespBody() :
            systemId_("system_id"),
            scInterfaceVersion_("sc_interface_version", SC_INTERFACE_VERSION)
        {}

        CString systemId_;
        TLV<OneByteInteger> scInterfaceVersion_;
    };

    BindReceiverResp::BindReceiverResp() : Pdu("BIND_RECEIVER_RESP"), body_(NULL)
    {
        body_ = new BindReceiverRespBody;
        SetCommandId(SMPP::BIND_RECEIVER_RESP);

        parameters_->Add(body_->systemId_);
        parameters_->Add(body_->scInterfaceVersion_);
    }

    BindReceiverResp::BindReceiverResp(const BindReceiverResp &rhs) : Pdu(rhs), body_(NULL)
    {
        body_ = new BindReceiverRespBody(*(rhs.body_));

        parameters_->Add(body_->systemId_);
        parameters_->Add(body_->scInterfaceVersion_);
    }

    BindReceiverResp& BindReceiverResp::operator =(const BindReceiverResp& rhs)
    {
        if (this == & rhs)
        {
            return *this;
        }

        Pdu::operator =(rhs);
        *body_ = *(rhs.body_);
        parameters_->Add(body_->systemId_);
        parameters_->Add(body_->scInterfaceVersion_);

        return *this;
    }

    BindReceiverResp::~BindReceiverResp()
    {
        if (NULL != body_)
        {
            delete body_;
            body_ = NULL;
        }
    }

    const std::string& BindReceiverResp::SystemId() const
    {
        return body_->systemId_.Value();
    }

    void BindReceiverResp::SetSystemId(const std::string &id)
    {
        body_->systemId_.SetValue(id);
    }

    void BindReceiverResp::SetScInterfaceVersion(uint32_t version)
    {
        TLV<OneByteInteger>::ValueType v;
        v.SetValue(version);
        body_->scInterfaceVersion_.SetValue(v);
    }

    uint32_t BindReceiverResp::ScInterfaceVersion() const
    {
        const TLV<OneByteInteger>::ValueType& v = body_->scInterfaceVersion_.Value();
        return v.Value();
    }

    void BindReceiverResp::SetData(const DataBuffer &data)
    {
        Pdu::SetData(data);

        const char* sysId = reinterpret_cast<const char*>(data.Data());
        const std::string id(sysId + 16);
        body_->systemId_.SetValue(id);
    }

    value_t BindReceiverResp::MinBodySize() const
    {
        return SYSTEM_ID_MAX_LEN + OneByteInteger().Size();
    }

    value_t BindReceiverResp::MaxBodySize() const
    {
        return SYSTEM_ID_MAX_LEN + TLV<OneByteInteger>("", SC_INTERFACE_VERSION).Size();
    }
}
