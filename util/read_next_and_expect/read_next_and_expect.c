#include <stdbool.h>
#include <stdint.h>
#include "../../data/esp001s_response.h"
#include "http_function_declarations.h"

bool read_next_and_expect(char *pattern, uint16_t startPositionOffset)
{
    while (*pattern != '\0')
    {
        char currentValue = *(rawResponse + startPositionOffset);
        if (*(pattern++) != currentValue)
            return false;
        startPositionOffset++;
    }
    return true;
}