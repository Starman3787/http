#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include "./response_parser/response_parser.c"
#include "./http_response_status/http_response_status.c"
#include "./http_header_parser/http_header_parser.c"
#include "./http_header_parser/http_header_structures.h"
#include "./util/find_header/find_header.c"
#include "./util/display_headers/display_headers.c"
#include "./util/free_headers/free_headers.c"
#include "./util/parse_date/parse_date.c"
#include "./http_body_parser/http_body_parser.c"
#include "./http_body_parser/http_body_structures.h"
#include "./util/display_body/display_body.c"
#include "./util/free_body/free_body.c"

void main(void)
{
    char *response = response_parser();
    printf("%s\n", response);

    uint16_t status = http_response_status(response);
    printf("%lu\n", status);

    uint8_t headersLength;
    char *headersEnd;
    Header **headers = http_header_parser(response, &headersLength, &headersEnd);

    display_headers(headers, headersLength);

    headersEnd++;

    Body *parsedBody = http_body_parser(headersEnd, headers, &headersLength);
    display_body(parsedBody);
    free_body(&parsedBody);

    Header *headerFound = find_header(headers, headersLength, "date");
    printf("%s\n", headerFound->value);
    time_t currentTime = parse_date(headerFound->value);
    printf("%lli\n", currentTime);

    free_headers(&headers, headersLength);
}