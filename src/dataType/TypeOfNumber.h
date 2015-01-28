#ifndef TYPEOFNUMBER_H
#define TYPEOFNUMBER_H

namespace SMPP
{
    enum TON_VALUE
    {
        TON_UNKNOWN = 0x00,
        TON_INTERNATIONAL = 0x01,
        TON_NATIONAL = 0x02,
        TON_NETWORK_SPECIFIC = 0x03,
        TON_SUBSCRIBER_NUMBER = 0x04,
        TON_ALPHANUMERIC = 0x05,
        TON_ABBREVIATED = 0x06
    };
}

#endif // TYPEOFNUMBER_H
