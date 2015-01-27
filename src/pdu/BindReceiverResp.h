#ifndef BINDRECEIVERRESP_H
#define BINDRECEIVERRESP_H

#include "Pdu.h"
#include <string>

namespace SMPP
{
    class BindReceiverResp : public Pdu
    {
    public:
        static const value_t SYSTEM_ID_MAX_LEN;

        BindReceiverResp();
        BindReceiverResp(const BindReceiverResp& rhs);
        BindReceiverResp& operator=(const BindReceiverResp& rhs);
        ~BindReceiverResp();

        const std::string& SystemId() const;
        void SetSystemId(const std::string& id);

        void SetScInterfaceVersion(uint32_t version);
        uint32_t ScInterfaceVersion() const;

        virtual void SetData(const DataBuffer &data);

    private:
        virtual value_t MinBodySize() const;
        virtual value_t MaxBodySize() const;

        class BindReceiverRespBody;
        BindReceiverRespBody* body_;
    };
}

#endif // BINDRECEIVERRESP_H
