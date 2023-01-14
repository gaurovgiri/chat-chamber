#include "utils.h"
#include <math.h>

int countDigits(int num)
{
    return (int)floor(log10(num)+1);
}