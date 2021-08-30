#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include "./http_header_parser/http_header_structures.h"
#include "./http_body_parser/http_body_structures.h"
#include "http_function_declarations.h"
#ifdef DMALLOC
#include "dmalloc.h"
#endif

int main(void)
{
    char *response = response_parser();
    printf("%s\n", response);

    uint16_t status = http_response_status(response);
    printf("%u\n", status);

    uint8_t headersLength;
    char *headersEnd;
    Header **headers = http_header_parser(response, &headersLength, &headersEnd);

    display_headers(headers, headersLength);

    headersEnd++;

    Body *parsedBody = http_body_parser(headersEnd, headers, headersLength);

    free(response);

    display_body(parsedBody);
    free_body(&parsedBody);

    Header *headerFound = find_header(headers, headersLength, "date");
    printf("%s\n", headerFound->value);
    time_t currentTime = parse_date(headerFound->value);
    printf("%li\n", currentTime);

    free_headers(&headers, headersLength);

    return 0;
}