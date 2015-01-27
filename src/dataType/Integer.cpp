#include "Integer.h"
#include <arpa/inet.h>
#include <limits>
#include <cassert>

namespace SMPP
{
    template <typename T>
    T SwapBytes(T val)
    {
        assert(NULL != "Not implemented !");
        return val;
    }

    template<>
    uint8_t SwapBytes(uint8_t val)
    {
        return val;
    }

    template<>
    uint16_t SwapBytes(uint16_t val)
    {
        return htons(val);
    }

    template<>
    uint32_t SwapBytes(uint32_t val)
    {
        return htonl(val);
    }

    template <typename T>
    value_t Integer<T>::MaxValue()
    {
        return std::numeric_limits<T>::max();
    }

    template <typename T>
    Integer<T>::Integer(const char* name, uint32_t value /* = 0*/) : PduDataType(name)
    {
        bzero(&data_[0], sizeof(T));
        SetValue(value);
    }

    template <typename T>
    Integer<T>::~Integer() {}

    template <typename T>
    const unsigned char* Integer<T>::Data() const
    {
        return &data_[0];
    }

    template <typename T>
    value_t Integer<T>::Size() const
    {
        return sizeof(T);
    }

    template <typename T>
    void Integer<T>::SetValue(value_t val)
    {
        const T theValue = T(val);
        if (value_t(theValue) < val)
        {
            std::stringstream s;
            s << __PRETTY_FUNCTION__ << " " << Name();
            s << " : value(" << val << ") bigger than the maximum allowed value(" << MaxValue() << ")";
            throw std::invalid_argument(s.str());
        }

        const T newVal =  SwapBytes<T>(theValue);
        const unsigned char* buf = reinterpret_cast<const unsigned char*>(&newVal);
        memcpy(&data_[0], buf, sizeof(newVal));
    }

    template <typename T>
    value_t Integer<T>::Value() const
    {
        T val = T(0);
        const unsigned char* buf = reinterpret_cast<const unsigned char*>(&data_[0]);
        memcpy(&val, buf, sizeof(T));
        return SwapBytes<T>(val);
    }

    template class Integer<unsigned char>;
    template class Integer<uint16_t>;
    template class Integer<uint32_t>;
}
