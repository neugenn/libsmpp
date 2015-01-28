#ifndef SERVICETYPE_H
#define SERVICETYPE_H

#include <string>

namespace SMPP
{
    enum SERVICE_TYPE
    {
        SERVICE_TYPE_NONE,
        SERVICE_TYPE_CMT,
        SERVICE_TYPE_CPT,
        SERVICE_TYPE_VMN,
        SERVICE_TYPE_VMA,
        SERVICE_TYPE_WAP,
        SERVICE_TYPE_USSD
    };

    const std::string& ServiceTypeValue(SERVICE_TYPE service);
    SERVICE_TYPE FromString(const std::string& service);
}

#endif // SERVICETYPE_H
