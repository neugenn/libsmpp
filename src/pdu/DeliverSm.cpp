#include "DeliverSm.h"
#include "Integer.h"
#include "COctetString.h"
#include "Parameters.h"

namespace SMPP
{
    const size_t DeliverSm::SERVICE_TYPE_MAX_LEN = 5; //bytes
    const size_t DeliverSm::SOURCE_ADDR_MAX_LEN = 20; //bytes
    const size_t DeliverSm::DESTINATION_ADDR_MAX_LEN = 20; //bytes

    class DeliverSm::DeliverSmBody
    {
    public:
        DeliverSmBody() :
            serviceType_("service_type"),
            sourceAddrTon_("source_addr_ton"),
            sourceAddrNpi_("source_addr_npi"),
            sourceAddr_("source_addr"),
            destAddrTon_("dest_addr_ton"),
            destAddrNpi_("dest_addr_npi"),
            destinationAddr_("destination_addr"),
            esmClass_("esm_class"),
            protocolId_("protocol_id"),
            priorityFlag_("priority_flag"),
            scheduleDeliveryTime_("schedule_delivery_time"),
            validityPeriod_("validity_period"),
            registeredDelivery_("registered_delivery"),
            replaceIfPresentFlag_("replace_if_present_flag"),
            dataCoding_("data_coding"),
            smDefaultMsgId_("sm_default_msg_id"),
            smLength_("sm_length"),
            shortMessage_("short_message")
        {
            serviceType_.SetValue(ServiceTypeValue(SERVICE_TYPE_NONE));
        }

        CString serviceType_;
        OneByteInteger sourceAddrTon_;
        OneByteInteger sourceAddrNpi_;
        CString sourceAddr_;
        OneByteInteger destAddrTon_;
        OneByteInteger destAddrNpi_;
        CString destinationAddr_;
        OneByteInteger esmClass_;
        OneByteInteger protocolId_;
        OneByteInteger priorityFlag_;
        CString scheduleDeliveryTime_;
        CString validityPeriod_;
        OneByteInteger registeredDelivery_;
        OneByteInteger replaceIfPresentFlag_;
        OneByteInteger dataCoding_;
        OneByteInteger smDefaultMsgId_;
        OneByteInteger smLength_;
        OctetString shortMessage_;
    };

    DeliverSm::DeliverSm() : Pdu("DELIVER_SM"), body_(NULL)
    {
        body_ = new DeliverSmBody;
        SetCommandId(SMPP::DELIVER_SM);

        parameters_->Add(body_->serviceType_);
        parameters_->Add(body_->sourceAddrTon_);
        parameters_->Add(body_->sourceAddrNpi_);
        parameters_->Add(body_->sourceAddr_);
        parameters_->Add(body_->destAddrTon_);
        parameters_->Add(body_->destAddrNpi_);
        parameters_->Add(body_->destinationAddr_);
        parameters_->Add(body_->esmClass_);
        parameters_->Add(body_->protocolId_);
        parameters_->Add(body_->priorityFlag_);
        parameters_->Add(body_->scheduleDeliveryTime_);
        parameters_->Add(body_->validityPeriod_);
        parameters_->Add(body_->registeredDelivery_);
        parameters_->Add(body_->replaceIfPresentFlag_);
        parameters_->Add(body_->dataCoding_);
        parameters_->Add(body_->smDefaultMsgId_);
        parameters_->Add(body_->smLength_);
        parameters_->Add(body_->shortMessage_);
    }

    DeliverSm::DeliverSm(const DeliverSm &rhs) : Pdu(rhs), body_(NULL)
    {
        body_ = new DeliverSmBody(*(rhs.body_));

        parameters_->Add(body_->serviceType_);
        parameters_->Add(body_->sourceAddrTon_);
        parameters_->Add(body_->sourceAddrNpi_);
        parameters_->Add(body_->sourceAddr_);
        parameters_->Add(body_->destAddrTon_);
        parameters_->Add(body_->destAddrNpi_);
        parameters_->Add(body_->destinationAddr_);
        parameters_->Add(body_->esmClass_);
        parameters_->Add(body_->protocolId_);
        parameters_->Add(body_->priorityFlag_);
        parameters_->Add(body_->scheduleDeliveryTime_);
        parameters_->Add(body_->validityPeriod_);
        parameters_->Add(body_->registeredDelivery_);
        parameters_->Add(body_->replaceIfPresentFlag_);
        parameters_->Add(body_->dataCoding_);
        parameters_->Add(body_->smDefaultMsgId_);
        parameters_->Add(body_->smLength_);
        parameters_->Add(body_->shortMessage_);
    }

    DeliverSm& DeliverSm::operator=(const DeliverSm &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        Pdu::operator =(rhs);
        *body_ = *(rhs.body_);

        parameters_->Add(body_->serviceType_);
        parameters_->Add(body_->sourceAddrTon_);
        parameters_->Add(body_->sourceAddrNpi_);
        parameters_->Add(body_->sourceAddr_);
        parameters_->Add(body_->destAddrTon_);
        parameters_->Add(body_->destAddrNpi_);
        parameters_->Add(body_->destinationAddr_);
        parameters_->Add(body_->esmClass_);
        parameters_->Add(body_->protocolId_);
        parameters_->Add(body_->priorityFlag_);
        parameters_->Add(body_->scheduleDeliveryTime_);
        parameters_->Add(body_->validityPeriod_);
        parameters_->Add(body_->registeredDelivery_);
        parameters_->Add(body_->replaceIfPresentFlag_);
        parameters_->Add(body_->dataCoding_);
        parameters_->Add(body_->smDefaultMsgId_);
        parameters_->Add(body_->smLength_);
        parameters_->Add(body_->shortMessage_);

        return *this;
    }

    DeliverSm::~DeliverSm()
    {
        if (NULL != body_)
        {
            delete body_;
        }
    }

    SERVICE_TYPE DeliverSm::ServiceType() const
    {
        const std::string& value = body_->serviceType_.Value();
        return FromString(value);
    }

    void DeliverSm::SetSourceAddrTon(TON_VALUE value)
    {
        body_->sourceAddrTon_.SetValue(value);
    }

    SMPP::TON_VALUE DeliverSm::SourceAddrTon() const
    {
        return static_cast<TON_VALUE>(body_->sourceAddrTon_.Value());
    }

    void DeliverSm::SetSourceAddrNpi(NPI value)
    {
        body_->sourceAddrNpi_.SetValue(value);
    }

    SMPP::NPI DeliverSm::SourceAddrNpi() const
    {
        return static_cast<NPI>(body_->sourceAddrNpi_.Value());
    }

    void DeliverSm::SetSourceAddr(const std::string &address)
    {
        body_->sourceAddr_.SetValue(address);
    }

    const std::string& DeliverSm::SourceAddr() const
    {
        return body_->sourceAddr_.Value();
    }

    void DeliverSm::SetDestAddrTon(TON_VALUE value)
    {
        body_->destAddrTon_.SetValue(value);
    }

    SMPP::TON_VALUE DeliverSm::DestAddrTon() const
    {
        return static_cast<TON_VALUE>(body_->destAddrTon_.Value());
    }

    void DeliverSm::SetDestAddrNpi(NPI value)
    {
        body_->destAddrNpi_.SetValue(value);
    }

    SMPP::NPI DeliverSm::DestAddrNpi() const
    {
        return static_cast<NPI>(body_->destAddrNpi_.Value());
    }

    void DeliverSm::SetDestinationAddr(const std::string &address)
    {
        body_->destinationAddr_.SetValue(address);
    }

    const std::string& DeliverSm::DestinationAddr() const
    {
        return body_->destinationAddr_.Value();
    }

    void DeliverSm::SetProtocolId(uint8_t pid)
    {
        body_->protocolId_.SetValue(pid);
    }

    uint8_t DeliverSm::ProtocolId() const
    {
        return body_->protocolId_.Value();
    }

    void DeliverSm::SetPriorityFlag(PRIORITY value)
    {
        body_->priorityFlag_.SetValue(value);
    }

    SMPP::PRIORITY DeliverSm::PriorityFlag() const
    {
        return static_cast<PRIORITY>(body_->priorityFlag_.Value());
    }

    uint8_t DeliverSm::SmLength() const
    {
        return body_->smLength_.Value();
    }

    void DeliverSm::SetShortMessage(const DataBuffer &data)
    {
        body_->shortMessage_.SetValue(data);
        body_->smLength_.SetValue(data.Size());
    }

    void DeliverSm::SetServiceType(SERVICE_TYPE type)
    {
        const std::string& value = ServiceTypeValue(type);
        body_->serviceType_.SetValue(value);
    }

    value_t DeliverSm::MinBodySize() const
    {
        return 15 * OneByteInteger().Size() + 48;
    }

    value_t DeliverSm::MaxBodySize() const
    {
        return MinBodySize();
    }
}



