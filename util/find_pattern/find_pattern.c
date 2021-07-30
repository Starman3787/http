#include <stdint.h>
#include "../../data/esp001s_response.h"

uint16_t find_pattern(const char *pattern, const size_t patternLength)
{
    uint8_t matchingChars = 0;
    uint16_t counter;
    for (counter = 0; matchingChars != patternLength; counter++)
    {
        char currentValue = *(rawResponse + counter);
        if (currentValue == *(pattern + matchingChars))
            matchingChars++;
        else
            matchingChars = 0U;
    }
    return counter;
}