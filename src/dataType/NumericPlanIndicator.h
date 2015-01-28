#ifndef NUMERICPLANINDICATOR_H
#define NUMERICPLANINDICATOR_H

namespace SMPP
{
    enum NPI
    {
        NPI_UNKNOWN = 0x00,
        NPI_ISDN = 0x01,
        NPI_DATA = 0x03,
        NPI_TELEX = 0x04,
        NPI_LAND_MOBILE = 0x06,
        NPI_NATIONAL = 0x08,
        NPI_PRIVATE = 0x09,
        NPI_ERMES = 0x0A,
        NPI_INTERNET = 0x0E,
        NPI_WAP = 0x12
    };
}

#endif // NUMERICPLANINDICATOR_H
