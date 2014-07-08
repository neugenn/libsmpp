#ifndef PDUHEADER_H
#define PDUHEADER_H

#include "PduDataType.h"
#include "CommandId.h"
#include "CommandStatus.h"
#include <stdexcept>

namespace SMPP
{
    class PduHeader : public PduDataType
    {
    public:
        /*!
         * \brief Creates an empty PduHeader object
         */
        PduHeader();

        /*!
         * \brief Creates a PduHeader object from a stream of bytes
         * \param[in] dataBuf The data buffer
         * \throw std::invalid_argument The data buffer is NULL
         */
        PduHeader(const PduHeader& rsh);

        PduHeader& operator=(const PduHeader& rsh);

        ~PduHeader();

        /*!
         * \brief
         * \return
         */
        virtual const unsigned char* Data() const;

        /*!
         * \brief Size
         * \return
         */
        virtual value_t Size() const;

        value_t CommandLength() const;
        void SetCommandLength(value_t len);

        SMPP::CommandId CommandId() const;
        void SetCommandId(SMPP::CommandId id);

        SMPP::CommandStatus CommandStatus() const;
        void SetCommandStatus(SMPP::CommandStatus status);

        value_t SequenceNumber() const;
        void SetSequenceNumber(value_t value);

    private:
        class PduHeaderPrivate;
        PduHeaderPrivate* impl_;

        friend std::ostream& operator<<(std::ostream& s, const PduHeader& h);
    };
}

#endif // PDUHEADER_H
