#include <stdio.h>
#include <stdint.h>
#include "./response_parser/response_parser.c"
#include "./http_response_status/http_response_status.c"
#include "./http_header_parser/http_header_parser.c"
#include "./http_header_parser/http_header_structures.h"
#include "./util/find_header/find_header.c"

void main(void)
{
    char *response = response_parser();
    printf("%s\n", response);
    uint16_t status = http_response_status(response);
    printf("%lu\n", status);
    uint8_t headersLength;
    Header **headers = http_header_parser(response, &headersLength);
    printf("%d\n", headersLength);
    for (uint8_t i = 0; i < headersLength; i++)
        printf("%s: %s\n", (*(headers + i))->key, (*(headers + i))->value);
    Header *headerFound = find_header(headers, headersLength, "date");
    printf("%s\n", headerFound->value);
}