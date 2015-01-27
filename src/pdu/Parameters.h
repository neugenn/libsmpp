#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "PduDataType.h"
#include "DataBuffer.h"
#include <vector>
#include <iostream>

namespace SMPP
{
    class Parameters : public PduDataType
    {
    public:
        Parameters();
        ~Parameters();

        virtual value_t Size() const;
        virtual const unsigned char* Data() const;

        size_t Count() const;
        void Add(const PduDataType& parameter);
        void Add(const Parameters& parameters);
        void Clear();

        void SetDataBuffer(const DataBuffer& buffer);

    private:
        std::vector<const PduDataType*> parameters_;
        mutable DataBuffer data_;
        DataBuffer readData_;

        friend std::ostream& operator<<(std::ostream& s, const SMPP::Parameters& parameters);
    };
}

#endif // PARAMETERS_H
