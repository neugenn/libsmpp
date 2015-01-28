#include "ServiceType.h"
#include <utility>
#include <map>
#include <iostream>

namespace SMPP
{
    class ServiceValues
    {
    public:
        static const std::string& GetValue(SERVICE_TYPE service)
        {
            return Services.values_.at(service);
        }

        static SERVICE_TYPE GetType(const std::string& value)
        {
            SERVICE_TYPE res = SERVICE_TYPE_NONE;
            std::map<SERVICE_TYPE, std::string>::const_iterator it = Services.values_.begin();
            std::map<SERVICE_TYPE, std::string>::const_iterator itEnd = Services.values_.end();
            for (; it != itEnd; ++it)
            {
                const std::pair<SERVICE_TYPE, std::string>& p = *it;
                if (value == p.second)
                {
                    res = p.first;
                    break;
                }
            }

            return res;
        }

    private:
        static ServiceValues Services;

        ServiceValues() : values_()
        {
            Init();
        }

        const std::map<SERVICE_TYPE, std::string>& GetMap() const
        {
            return values_;
        }

        void Init()
        {
            values_.insert(std::pair<SERVICE_TYPE, std::string>(SERVICE_TYPE_NONE, ""));
            values_.insert(std::pair<SERVICE_TYPE, std::string>(SERVICE_TYPE_CMT, "CMT"));
            values_.insert(std::pair<SERVICE_TYPE, std::string>(SERVICE_TYPE_CPT, "CPT"));
            values_.insert(std::pair<SERVICE_TYPE, std::string>(SERVICE_TYPE_VMN, "VMN"));
            values_.insert(std::pair<SERVICE_TYPE, std::string>(SERVICE_TYPE_VMA, "WMA"));
            values_.insert(std::pair<SERVICE_TYPE, std::string>(SERVICE_TYPE_WAP, "WAP"));
            values_.insert(std::pair<SERVICE_TYPE, std::string>(SERVICE_TYPE_USSD, "USSD"));

            /*
            std::map<SERVICE_TYPE, std::string>::const_iterator it = values_.begin();
            std::map<SERVICE_TYPE, std::string>::const_iterator itEnd = values_.end();
            for (; it != itEnd; ++it)
            {
                const std::pair<SERVICE_TYPE, std::string>& p = *it;
                std::cout << p.first << " " << p.second << std::endl;
            }
            */
        }

        std::map<SERVICE_TYPE, std::string> values_;
    };

    ServiceValues ServiceValues::Services;

    const std::string& ServiceTypeValue(SERVICE_TYPE service)
    {
        return ServiceValues::GetValue(service);
    }

    SERVICE_TYPE FromString(const std::string &service)
    {
        return ServiceValues::GetType(service);
    }
}
