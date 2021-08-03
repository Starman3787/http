#include <stdlib.h>
#include <stdio.h>
#include "../../http_header_parser/http_header_structures.h"

void free_headers(Header ***headers, uint8_t headersLength)
{
    for (uint8_t i = 0; i < headersLength; i++)
    {
        printf("FREEING KEY: %s\n", (*(*headers + i))->key);
        free((*(*headers + i))->key);
        printf("FREEING VALUE: %s\n", (*(*headers + i))->value);
        free((*(*headers + i))->value);
    }
    free(*headers);
}