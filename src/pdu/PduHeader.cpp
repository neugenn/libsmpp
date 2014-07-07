#include "PduHeader.h"
#include "CommandStatus.h"
#include "Integer.h"
#include "IntegerPrivate.h"

namespace SMPP
{
    class PduHeader::PduHeaderPrivate
    {
    public:
        PduHeaderPrivate() :
        commandLen_("command_len"),
        commandId_("command_id"),
        commandStatus_("command_status"),
        sequenceNum_("sequence_number"),
        data_()
        {}

        PduHeaderPrivate(const unsigned char*& data) :
        commandLen_(data, "command_len"),
        commandId_(data, "command_id"),
        commandStatus_(data, "command_status"),
        sequenceNum_(data, "sequence_number"),
        data_()
        {}

        unsigned const char* Data()
        {
            bzero(&data_[0], sizeof(data_));

            memcpy(data_, commandLen_.Data(), commandLen_.Size());
            size_t offset = commandLen_.Size();

            memcpy(data_ + offset, commandId_.Data(), commandId_.Size());
            offset += commandId_.Size();

            memcpy(data_ + offset, commandStatus_.Data(), commandStatus_.Size());
            offset += commandStatus_.Size();

            memcpy(data_ + offset, sequenceNum_.Data(), sequenceNum_.Size());
            return &data_[0];
        }

        static const size_t Size = 16; //bytes

        SMPP::FourByteInteger commandLen_;
        SMPP::FourByteInteger commandId_;
        SMPP::FourByteInteger commandStatus_;
        SMPP::FourByteInteger sequenceNum_;
        unsigned char data_[Size];
    };

    PduHeader::PduHeader() :
    PduDataType(),
    impl_(new PduHeaderPrivate)
    {
        this->SetCommandStatus(SMPP::ESME_ROK);
    }

    PduHeader::PduHeader(const unsigned char*& data) :
    PduDataType(),
    impl_(new PduHeaderPrivate(data))
    {
    }

    PduHeader::PduHeader(const PduHeader &rsh) :
    PduDataType(rsh),
    impl_(NULL)
    {
        const unsigned char* pc = rsh.Data();
        impl_ = new PduHeaderPrivate(pc);
    }

    PduHeader& PduHeader::operator=(const PduHeader& rsh)
    {
        if (this != &rsh)
        {
            this->SetCommandLength(rsh.CommandLength());
            this->SetCommandId(rsh.CommandId());
            this->SetCommandStatus(rsh.CommandStatus());
            this->SetSequenceNumber(rsh.SequenceNumber());
        }

        return *this;
    }

    PduHeader::~PduHeader()
    {
        if (NULL != impl_)
        {
            delete impl_;
        }
    }

    value_t PduHeader::CommandLength() const
    {
        return impl_->commandLen_.Value();
    }

    void PduHeader::SetCommandLength(value_t len)
    {
        impl_->commandLen_.SetValue(len);
    }

    SMPP::CommandId PduHeader::CommandId() const
    {
        return SMPP::CommandId(impl_->commandId_.Value());
    }

    void PduHeader::SetCommandId(SMPP::CommandId id)
    {
        impl_->commandId_.SetValue(id);
    }

    SMPP::CommandStatus PduHeader::CommandStatus() const
    {
        return SMPP::CommandStatus(impl_->commandStatus_.Value());
    }

    void PduHeader::SetCommandStatus(SMPP::CommandStatus status)
    {
        impl_->commandStatus_.SetValue(status);
    }

    value_t PduHeader::SequenceNumber() const
    {
        return impl_->sequenceNum_.Value();
    }

    void PduHeader::SetSequenceNumber(value_t val)
    {
        impl_->sequenceNum_.SetValue(val);
    }

    void PduHeader::GetFormattedContent(std::string &res) const
    {
        std::stringstream s;
        s << "command_len: 0x" << impl_->commandLen_ << " (" << impl_->commandLen_.Value() << ")" << std::endl;
        s << "command_id: 0x" << impl_->commandId_ << std::endl;
        s << "command_status: 0x" << impl_->commandStatus_ << std::endl;
        s << "sequence_number: 0x" << impl_->sequenceNum_ << " (" << impl_->sequenceNum_.Value() << ")" << std::endl;

        res = s.str();
    }

    const unsigned char* PduHeader::Data() const
    {
        return impl_->Data();
    }

    size_t PduHeader::Size() const
    {
        return PduHeaderPrivate::Size;
    }
}
