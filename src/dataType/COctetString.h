#ifndef COCTETSTRING_H
#define COCTETSTRING_H

#include "PduDataType.h"
#include "HexValidation.h"
#include "DefaultValidation.h"
#include "DataBuffer.h"
#include <string>
#include <stdexcept>

namespace SMPP
{
    /*!
     * @brief ASCII characters
     */
    template <typename T>
    class COctetString : public PduDataType
    {
    public:
        /*!
         * \brief COctetString Creates an empty string containing only the NULL character
         */
        COctetString(const char* name = "");
        ~COctetString();

        virtual const unsigned char* Data() const;
        virtual value_t Size() const;
        const std::string& Value() const;
        void SetValue(const std::string& value);

    private:
        T validator_;
        std::string data_;
    };

    /*!
     * @brief CString A series of ASCII characters terminated with the NULL character
     */
    typedef COctetString<AsciiValidation> CString;

    /*!
     * @brief CDecimalString A series of ASCII characters, each character representing a decimal digit (0-9) \
     * and terminated with the NULL character
     */
    typedef COctetString<DecimalValidation> CDecimalString;

    /*!
     * @brief CHexString A series of ASCII characters, each character representing a hexadecimal digit (0-F) \
     * and terminated with the NULL character
     */
    typedef COctetString<HexValidation> CHexString;

    template <>
    class COctetString<DefaultValidation> : public PduDataType
    {
    public:
        COctetString(const char* name = "") : PduDataType(name),
            validator_(),
            data_()
        {}

        ~COctetString() {}

        virtual const unsigned char* Data() const
        {
            return data_.Data();
        }

        virtual value_t Size() const
        {
            return data_.Size();
        }

        void SetValue(const DataBuffer& buf)
        {
            data_ = buf;
        }

    private:
        DefaultValidation validator_;
        DataBuffer data_;
    };

    typedef COctetString<DefaultValidation> OctetString;
}

#endif // COCTETSTRING_H
