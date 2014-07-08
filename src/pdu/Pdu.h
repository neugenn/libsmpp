#ifndef PDU_H
#define PDU_H

#include "PduDataType.h"
#include "CommandId.h"
#include "CommandStatus.h"
#include "PduHeader.h"
#include <string>

namespace SMPP
{
    class Pdu : public PduDataType
    {
    public:
        static value_t MaxSequenceNumber();

        /*!
         * \brief Creates an empty Pdu object
         */
        Pdu();

        /*!
         * \brief Creates a Pdu object with a specific header
         * \param data
         */
        Pdu(const PduHeader& h);

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

        SMPP::CommandStatus GetCommandError() const;


        /*!
         * @brief The minimum size of the PDU
         */
        value_t MinSize() const;

        /*!
         * @brief The maximum size of the PDU
         */
        value_t MaxSize() const;

        bool IsValid() const;

    protected:
        virtual void GetFormattedContent(std::string& s) const;
        void UpdateCommandLength();

    private:
        virtual value_t GetMinSize() const = 0;
        virtual value_t GetMaxSize() const = 0;
        bool IsValidHeader() const;
        virtual bool IsValidBody() const;

    protected:
        PduHeader header_;
        friend std::ostream& operator<<(std::ostream& s, const SMPP::Pdu& pdu);
    };

    bool operator==(const SMPP::Pdu& lsh, const SMPP::Pdu& rsh);
    bool operator!=(const SMPP::Pdu& lsh, const SMPP::Pdu& rsh);
}

#endif // PDU_H
