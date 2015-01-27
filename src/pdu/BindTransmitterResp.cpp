#include "BindTransmitterResp.h"
#include "PduHeader.h"

namespace SMPP
{
    const size_t BindTransmitterResp::SystemIdMaxLen = 16; //bytes
    const size_t MIN_SIZE = PduHeader().Size() + CString().Size();

    BindTransmitterResp::BindTransmitterResp() :
    Pdu(),
    systemId_("system_id"),
    data_(NULL)
    {
        header_.SetCommandId(SMPP::BIND_TRANSMITTER_RESP);
        header_.SetCommandLength(MIN_SIZE);
    }

    BindTransmitterResp::BindTransmitterResp(const PduHeader& h, const unsigned char* body) :
    Pdu(h),
    systemId_(body, SystemIdMaxLen, "system_id"),
    data_(NULL)
    {
    }

    BindTransmitterResp::BindTransmitterResp(const BindTransmitterResp& rsh) :
    Pdu(rsh),
    systemId_(rsh.systemId_),
    data_(NULL)
    {
    }

    BindTransmitterResp& BindTransmitterResp::operator=(const BindTransmitterResp& rsh)
    {
        if (this == &rsh)
        {
            return *this;
        }

        Pdu::operator =(rsh);
        systemId_ = rsh.systemId_;
        data_ = NULL;

        return *this;
    }

    BindTransmitterResp::~BindTransmitterResp()
    {
       if (NULL != data_)
       {
           delete [] data_;
       }
    }

    void BindTransmitterResp::GetFormattedContent(std::string &s) const
    {
        s.clear();
        Pdu::GetFormattedContent(s);
        std::stringstream str;
        str << s;
        str << "system_id: " << systemId_ << " (" << systemId_.Value() << ")" << std::endl;
        s = str.str();
    }

    value_t BindTransmitterResp::MinBodySize() const
    {
        return MIN_SIZE;
    }

    value_t BindTransmitterResp::MaxBodySize() const
    {
        return header_.Size() + SystemIdMaxLen;
    }

    const unsigned char* BindTransmitterResp::Data() const
    {
        if (NULL != data_)
        {
            delete [] data_;
        }

        const size_t size = Size();
        unsigned char* buf = new unsigned char[size];

        memcpy(buf, header_.Data(), header_.Size());
        memcpy(buf + header_.Size(), systemId_.Data(), systemId_.Size());

        data_ = buf;
        return data_;
    }

    value_t BindTransmitterResp::Size() const
    {
        const size_t size = header_.Size() + systemId_.Size();
        return size;
    }

    void BindTransmitterResp::SetSystemId(const std::string &id)
    {
        std::string s(id);
        if (s.size() > SystemIdMaxLen)
        {
            s = std::string(id.c_str(), SystemIdMaxLen);
        }

        systemId_.SetValue(s);
        this->UpdateCommandLength();
    }

    const std::string& BindTransmitterResp::GetSystemId() const
    {
        return systemId_.Value();
    }
}
