#include "Parameters.h"

namespace SMPP
{
    Parameters::Parameters() : PduDataType(), parameters_(), data_()
    {}

    Parameters::~Parameters()
    {}

    value_t Parameters::Size() const
    {
        value_t size = 0;
        std::vector<const PduDataType*>::const_iterator it = parameters_.begin();
        std::vector<const PduDataType*>::const_iterator itEnd = parameters_.end();
        for (; it != itEnd; ++it)
        {
            const PduDataType* item = *it;
            size += item->Size();
        }

        return size;
    }

    const unsigned char* Parameters::Data() const
    {
        if (data_.Size() != Size())
        {
            data_.Alloc(Size());
        }

        data_.Clear();

        size_t offset = size_t(0);
        unsigned char* data = data_.Data();

        std::vector<const PduDataType*>::const_iterator it = parameters_.begin();
        std::vector<const PduDataType*>::const_iterator itEnd = parameters_.end();
        for (; it != itEnd; ++it)
        {
            const PduDataType* item = *it;
            memcpy(data + offset, item->Data(), item->Size());
            offset += item->Size();
        }

        return data;
    }

    size_t Parameters::Count() const
    {
        return parameters_.size();
    }

    void Parameters::Add(const PduDataType& parameter)
    {
        parameters_.push_back(&parameter);
    }

    void Parameters::Add(const Parameters &parameters)
    {
        std::vector<const PduDataType*>::const_iterator it = parameters.parameters_.begin();
        std::vector<const PduDataType*>::const_iterator itEnd = parameters.parameters_.end();
        for (; it != itEnd; ++it)
        {
            parameters_.push_back(*it);
        }
    }

    void Parameters::Clear()
    {
        parameters_.clear();
    }

    void Parameters::SetDataBuffer(const DataBuffer &buffer)
    {
        readData_ = buffer;
    }

    std::ostream& operator<<(std::ostream& s, const SMPP::Parameters& parameters)
    {
        std::vector<const PduDataType*>::const_iterator it = parameters.parameters_.begin();
        std::vector<const PduDataType*>::const_iterator itEnd = parameters.parameters_.end();
        for (; it != itEnd; ++it)
        {
            const PduDataType* item = *it;
            s << *item;
        }

        return s;
    }
}
