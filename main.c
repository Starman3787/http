#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "./response_parser/response_parser.c"
#include "./http_response_status/http_response_status.c"
#include "./http_header_parser/http_header_parser.c"
#include "./http_header_parser/http_header_structures.h"
#include "./util/find_header/find_header.c"
#include "./util/parse_date/parse_date.c"

void main(void)
{
    char *response = response_parser();
    printf("%s\n", response);
    uint16_t status = http_response_status(response);
    printf("%lu\n", status);
    uint8_t headersLength;
    char *headersEnd;
    Header **headers = http_header_parser(response, &headersLength, headersEnd);
    printf("%d\n", headersLength);
    for (uint8_t i = 0; i < headersLength; i++)
        printf("%s: %s\n", (*(headers + i))->key, (*(headers + i))->value);
    Header *headerFound = find_header(headers, headersLength, "date");
    printf("%s\n", headerFound->value);
    time_t currentTime = parse_date(headerFound->value);
    printf("%lli\n", currentTime);
}