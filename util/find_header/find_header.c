#include <stdint.h>
#include <string.h>
#include "../../http_header_parser/http_header_structures.h"
#include "http_function_declarations.h"

Header *find_header(Header **headers, uint8_t headersLength, char *key)
{
    for (; headersLength--; *(headers++))
        if (strcmp((*headers)->key, key) == 0)
            return *headers;
    return NULL;
}