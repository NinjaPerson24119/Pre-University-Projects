#ifndef CTM_STRINGCONVERSIONS_H
#define CTM_STRINGCONVERSIONS_H

#include <stdexcept>
#include <cmath>

namespace ctm
{

int StringToInteger(const char *Start, unsigned int Length);
unsigned int StringToUnsignedInteger(const char *Start, unsigned int Length);

}

#endif