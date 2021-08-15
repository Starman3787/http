#ifndef FIND_HEADER_C
#define FIND_HEADER_C

#include <stdint.h>
#include <string.h>
#include "../../http_header_parser/http_header_structures.h"
#include "../to_lower_case/to_lower_case.h"

Header *find_header(Header **headers, uint8_t headersLength, char *key)
{
    to_lower_case(key);
    for (; headersLength--; *(headers++))
        if (strcmp((*headers)->key, key) == 0)
            return *headers;
    return NULL;
}

#endif