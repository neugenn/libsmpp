#ifndef INTEGER_PRIVATE_H
#define INTEGER_PRIVATE_H

#include "Integer.h"

namespace SMPP
{
    /*!
     * @brief OneByteInteger Unsigned value containing 2 octets
     */
    typedef Integer<uint16_t> TwoByteInteger;

    /*!
     * @brief OneByteInteger Unsigned value containing 4 octets
     */
    typedef Integer<uint32_t> FourByteInteger;
}

#endif // INTEGER_PRIVATE_H
