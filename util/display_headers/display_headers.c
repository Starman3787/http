#include <stdio.h>
#include <stdint.h>
#include "../../http_header_parser/http_header_structures.h"
#include "http_function_declarations.h"

void display_headers(Header **headers, uint8_t headersLength)
{
    for (uint8_t i = 0; i < headersLength; i++)
        printf("%s: %s\n", (*(headers + i))->key, (*(headers + i))->value);
}