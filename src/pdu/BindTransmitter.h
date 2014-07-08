#ifndef BINDTRANSMITTER_H
#define BINDTRANSMITTER_H

#include "Pdu.h"

namespace SMPP
{
    /*!
     * @brief BIND_TRANSMITTER PDU
     */
    class BindTransmitter : public Pdu
    {
    public:
        /*!
         * @brief The max lenght of the system_id, including the NULL terminating character
         */
        static const value_t SYSTEM_ID_MAX_LEN;

        /*!
         * @brief The max lenght of the password, including the NULL terminating character
         */
        static const value_t PASSWORD_MAX_LEN;

        /*!
         * @brief The max lenght of the system_type, including the NULL terminating character
         */
        static const value_t SYSTEM_TYPE_MAX_LEN;

        /*!
         * @brief The max lenght of the address_range, including the NULL terminating character
         */
        static const value_t ADDRESS_RANGE_MAX_LEN;

        /*!
         * @brief Creates an empty BindTransmitter object
         */
        BindTransmitter();

        /*!
         * @brief Creates a BindTransmitter object from a stream of bytes
         * @param[in] data Host byte order data buffer
         * @param[in] len The length of the data buffer
         * @throw std::invalid_argument The data buffer is NULL
         */
        BindTransmitter(const PduHeader&h, const unsigned char* body);

        ~BindTransmitter();

        BindTransmitter(const BindTransmitter& rsh);
        BindTransmitter& operator=(const BindTransmitter& rhs);

        /*!
         * @brief Data The data in host byte order
         */
        virtual const unsigned char* Data() const;

        /*!
         * @brief The size of the data buffer
         */
        virtual value_t Size() const;

    private:
        virtual value_t GetMinSize() const;
        virtual value_t GetMaxSize() const;
        virtual void GetFormattedContent(std::string &s) const;
        virtual bool IsValidHeader() const;

    private:
        class BindTransmitterBody;
        BindTransmitterBody* impl_;
    };
}

#endif // BINDTRANSMITTER_H
