#ifndef PDU_H
#define PDU_H

#include "PduDataType.h"
#include "CommandId.h"
#include "CommandStatus.h"
#include "DataBuffer.h"

namespace SMPP
{
    class Parameters;

    class Pdu : public PduDataType
    {
    public:
        static value_t MaxSequenceNumber();

        Pdu();
        Pdu(const Pdu& rhs);
        Pdu& operator=(const Pdu& rhs);
        virtual ~Pdu();

        value_t CommandLength() const;
        SMPP::CommandId CommandId() const;
        SMPP::CommandStatus CommandStatus() const;
        void SetCommandStatus(SMPP::CommandStatus status);
        value_t SequenceNumber() const;

        /*!
         * \brief SetSequenceNumber
         * \param value
         * \throw std::invalid_argument The value exeeds the maximum allowed value
         */
        void SetSequenceNumber(value_t value);

        /*!
         * @brief The minimum size of the PDU
         */
        value_t MinSize() const;

        /*!
         * @brief The maximum size of the PDU
         */
        value_t MaxSize() const;

        virtual value_t Size() const;

        virtual const unsigned char* Data() const;

        virtual void SetData(const DataBuffer& data);

    protected:
        Pdu(const char* name);
        void SetCommandId(SMPP::CommandId id);

    private:
        virtual value_t MinBodySize() const = 0;
        virtual value_t MaxBodySize() const = 0;
        void Update();

        class PduPrivate;
        PduPrivate* impl_;

    protected:
        Parameters* parameters_;

        friend std::ostream& operator<<(std::ostream& s, const SMPP::Pdu& pdu);
    };

    bool operator==(const SMPP::Pdu& lsh, const SMPP::Pdu& rsh);
    bool operator!=(const SMPP::Pdu& lsh, const SMPP::Pdu& rsh);
}

#endif // PDU_H
