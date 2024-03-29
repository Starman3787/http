#include <stdint.h>
#include <math.h>
#include <string.h>
#include "./hex_to_int.h"
#include "http_function_declarations.h"
#ifdef DMALLOC
#include "dmalloc.h"
#endif

uint32_t hex_to_int(char *hex)
{
    uint32_t total = 0;
    while (*hex != '\0')
        total += hex_char_to_int(*hex) * pow(16, (strlen(hex++) - 1));
    return total;
}