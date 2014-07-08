#include "COctetString.h"
#include <iomanip>

namespace SMPP
{
    template <typename T>
    COctetString<T>::COctetString(const char* name) :
        PduDataType(name),
        validator_(T()),
        data_()
    {
    }

    template <typename T>
    COctetString<T>::COctetString(const unsigned char*& data, size_t maxlen, const char* name) :
    PduDataType(name),
    validator_(T()),
    data_()
    {
        if (NULL == data)
        {
            std::stringstream s;
            s << __PRETTY_FUNCTION__ << " " << this->Name();
            s << " : NULL data buffer !";
            throw std::invalid_argument(s.str());
        }

        const char* asciidata = reinterpret_cast<const char*>(data);
        data_ = std::string(asciidata);
        if (data_.size() >= maxlen)
        {
            data_ = std::string(asciidata, maxlen - 1);
        }

        const unsigned char* toValidate = reinterpret_cast<const unsigned char*>(data_.c_str());
        if (!validator_.IsValid(toValidate, data_.size() + 1))
        {
            std::stringstream s;
            s << __PRETTY_FUNCTION__ << " " << this->Name() << " : " << maxlen;
            s << " : Invalid data !";
            throw std::invalid_argument(s.str());
        }

        data += (data_.size() + 1);
    }

    template <typename T>
    COctetString<T>::~COctetString()
    {}

    template <typename T>
    const unsigned char* COctetString<T>::Data() const
    {
        return reinterpret_cast<const unsigned char*>(data_.c_str());
    }

    template <typename T>
    value_t COctetString<T>::Size() const
    {
        return data_.size() + 1;
    }

    template <typename T>
    const std::string& COctetString<T>::Value() const
    {
        return data_;
    }

    template <typename T>
    void COctetString<T>::SetValue(std::string &value)
    {
        data_ = value;
        validator_.IsValid(this->Data(), this->Size());
    }

    template class COctetString<AsciiValidation>;
    template class COctetString<DecimalValidation>;
    template class COctetString<HexValidation>;
}
