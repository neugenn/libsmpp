#include "Pdu.h"
#include "Integer.h"
#include "PduHeader.h"
#include "DataBuffer.h"
#include "Parameters.h"
#include <arpa/inet.h>
#include <stdexcept>
#include <iostream>
#include <cassert>

namespace SMPP
{
    class Pdu::PduPrivate
    {
    public:
        static const size_t HEADER_SIZE;

        PduPrivate() :
            commandLen_("command_len"),
            commandId_("command_id"),
            commandStatus_("command_status"),
            sequenceNum_("sequence_number")
        {
        }

        PduPrivate(const PduPrivate& rhs) :
            commandLen_(rhs.commandLen_),
            commandId_(rhs.commandId_),
            commandStatus_(rhs.commandStatus_),
            sequenceNum_(rhs.sequenceNum_)
        {
        }

        PduPrivate& operator=(const PduPrivate& rhs)
        {
            if (this == &rhs)
            {
                return *this;
            }

            commandLen_ = rhs.commandLen_;
            commandId_ = rhs.commandId_;
            commandStatus_ = rhs.commandStatus_;
            sequenceNum_ = rhs.sequenceNum_;

            return *this;
        }

        SMPP::FourByteInteger commandLen_;
        SMPP::FourByteInteger commandId_;
        SMPP::FourByteInteger commandStatus_;
        SMPP::FourByteInteger sequenceNum_;
    };

    const size_t Pdu::PduPrivate::HEADER_SIZE = 16; //bytes

    value_t Pdu::MaxSequenceNumber()
    {
        return 0x7FFFFFFF;
    }

    Pdu::Pdu() : PduDataType(), impl_(NULL), parameters_(NULL)
    {
        impl_ = new PduPrivate;
        parameters_ = new Parameters;
        Update();
    }

    Pdu::Pdu(const Pdu &rhs) : PduDataType(rhs), impl_(NULL), parameters_(NULL)
    {
        impl_ = new PduPrivate(*(rhs.impl_));
        parameters_ = new Parameters;
        Update();
    }

    Pdu& Pdu::operator =(const Pdu& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        PduDataType::operator=(rhs);
        *impl_ = *(rhs.impl_);
        Update();

        return *this;
    }

    Pdu::~Pdu()
    {
        if (NULL != parameters_)
        {
            delete parameters_;
            parameters_ = NULL;
        }

        if (NULL != impl_)
        {
            delete impl_;
        }
    }

    value_t Pdu::CommandLength() const
    {
        impl_->commandLen_.SetValue(Size());
        return impl_->commandLen_.Value();
    }

    SMPP::CommandId Pdu::CommandId() const
    {
        return SMPP::CommandId(impl_->commandId_.Value());
    }

    SMPP::CommandStatus Pdu::CommandStatus() const
    {
        return SMPP::CommandStatus(impl_->commandStatus_.Value());
    }

    void Pdu::SetCommandStatus(SMPP::CommandStatus status)
    {
        impl_->commandStatus_.SetValue(status);
    }

    value_t Pdu::SequenceNumber() const
    {
        return impl_->sequenceNum_.Value();
    }

    void Pdu::SetSequenceNumber(value_t value)
    {
        if (value > Pdu::MaxSequenceNumber())
        {
            throw std::invalid_argument("Sequence number overflow !");
        }

        impl_->sequenceNum_.SetValue(value);
    }

    value_t Pdu::MinSize() const
    {
        return PduPrivate::HEADER_SIZE + MinBodySize();
    }

    value_t Pdu::MaxSize() const
    {
        return PduPrivate::HEADER_SIZE + MaxBodySize();
    }

    void Pdu::SetCommandId(SMPP::CommandId id)
    {
        impl_->commandId_.SetValue(id);
    }

    void Pdu::Update()
    {
        assert(NULL != parameters_);

        parameters_->Clear();
        parameters_->Add(impl_->commandLen_);
        parameters_->Add(impl_->commandId_);
        parameters_->Add(impl_->commandStatus_);
        parameters_->Add(impl_->sequenceNum_);
    }

    const unsigned char* Pdu::Data() const
    {
        impl_->commandLen_.SetValue(Size());
        return parameters_->Data();
    }

    void Pdu::SetData(const DataBuffer &data)
    {
        uint32_t value(0);
        unsigned char* buf = reinterpret_cast<unsigned char*>(&value);
        memcpy(buf, data.Data(), 4);
        impl_->commandLen_.SetValue(htonl(value));

        memcpy(buf, data.Data() + 4, 4);
        impl_->commandId_.SetValue(htonl(value));

        memcpy(buf, data.Data() + 8, 4);
        impl_->commandStatus_.SetValue(htonl(value));

        memcpy(buf, data.Data() + 12, 4);
        impl_->sequenceNum_.SetValue(htonl(value));
    }

    value_t Pdu::Size() const
    {
        return parameters_->Size();
    }

    Pdu::Pdu(const char *name) : PduDataType(name), impl_(NULL), parameters_(NULL)
    {
        impl_ = new PduPrivate;
        parameters_ = new Parameters;
        Update();
    }

    std::ostream& operator<<(std::ostream& s, const SMPP::Pdu& pdu)
    {
        pdu.impl_->commandLen_.SetValue(pdu.Size());

        s << pdu.Name() << std::endl;
        s << *pdu.parameters_;
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
}
