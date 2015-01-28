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
    void COctetString<T>::SetValue(const std::string &value)
    {
        data_ = value;
        validator_.IsValid(this->Data(), this->Size());
    }

    /*
    template <>
    COctetString<DefaultValidation>::COctetString(const char *name) :
        PduDataType(name),
        validator_(),
        data_()
    {}

    template<>
    COctetString<DefaultValidation>::~COctetString()
    {}

    template <>
    const unsigned char* COctetString<DefaultValidation>::Data() const
    {
        return data_.Data();
    }

    template <>
    value_t COctetString<DefaultValidation>::Size() const
    {
        return data_.Size();
    }

    template<>
    void COctetString<DefaultValidation>::SetValue(const DataBuffer& buf)
    {
        data_ = buf;
    }
    */

    template class COctetString<AsciiValidation>;
    template class COctetString<DecimalValidation>;
    template class COctetString<HexValidation>;
    //template class COctetString<DefaultValidation>;
}
