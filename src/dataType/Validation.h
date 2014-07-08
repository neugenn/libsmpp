#ifndef VALIDATION_H
#define VALIDATION_H

#include "PduDataType.h"

namespace SMPP
{
    /*!
     * @brief The interface of the validation algorithm used by a COctetString
     */
    class Validation
    {
    public:
        Validation() {}
        virtual ~Validation() {}

    public:
        virtual bool IsValid(const unsigned char* data, value_t size) const = 0;
    };
}

#endif // VALIDATION_H
