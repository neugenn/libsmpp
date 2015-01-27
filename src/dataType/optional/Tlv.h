#ifndef TLV_H
#define TLV_H

#include "Integer.h"
#include "DataBuffer.h"
#include "PduDataType.h"
#include <cassert>

namespace SMPP
{
    enum TLV_TAG
    {
        SC_INTERFACE_VERSION = 0x0210
    };

    template <typename T>
    class TLV : public PduDataType
    {
    public:
        typedef T ValueType;

        TLV(const char* name, TLV_TAG tagId) :
        PduDataType((std::string("TLV : ") + std::string(name)).c_str()),
          tag_("Tag", tagId),
          length_("Length"),
          value_("Value"),
          buffer_() {}

        ~TLV() {}

        size_t Length() const
        {
            return length_.Value();
        }

    private:
        void SetLength(size_t value)
        {
            length_.SetValue(value);
        }

    public:
        const ValueType& Value() const
        {
            return value_;
        }

        void SetValue(const ValueType& value)
        {
            this->SetLength(value.Size());
           value_ = value;
        }

        virtual value_t Size() const
        {
            return (0 == length_.Value()) ? 0 : (tag_.Size() + length_.Size() + length_.Value());
        }

        virtual const unsigned char* Data() const
        {
            if (0 == this->Size())
            {
                return NULL;
            }

            assert(length_.Value() == value_.Size());

            buffer_.Alloc(this->Size());
            unsigned char* data = buffer_.Data();

            memcpy(data, tag_.Data(), tag_.Size());
            size_t offset = tag_.Size();

            memcpy(data + offset, length_.Data(), length_.Size());
            offset += length_.Size();

            memcpy(data + offset, value_.Data(), value_.Size());
            return data;
        }

    private:
        TwoByteInteger tag_;
        TwoByteInteger length_;
        T value_;
        mutable DataBuffer buffer_;
    };
}

#endif // TLV_H
