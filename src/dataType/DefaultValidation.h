#ifndef DEFAULTVALIDATION_H
#define DEFAULTVALIDATION_H

#include "Validation.h"

namespace SMPP
{
    class DefaultValidation : public Validation
    {
    public:
        virtual bool IsValid(const unsigned char * /*data*/, value_t /*size*/) const;
    };
}

#endif // DEFAULTVALIDATION_H
