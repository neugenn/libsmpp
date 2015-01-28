#include "DefaultValidation.h"

namespace SMPP
{
    bool DefaultValidation::IsValid(const unsigned char * /*data*/, value_t /*size*/) const
    {
        return true;
    }
}
