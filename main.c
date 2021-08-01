#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include "./response_parser/response_parser.c"
#include "./http_response_status/http_response_status.c"
#include "./http_header_parser/http_header_parser.c"
#include "./http_header_parser/http_header_structures.h"
#include "./util/find_header/find_header.c"
#include "./util/parse_date/parse_date.c"
#include "./http_body_parser/http_body_parser.c"
#include "./http_body_parser/http_body_structures.h"
#include "./util/hex_to_int/hex_to_int.c"
#include "./util/display_json/display_json.c"

void main(void)
{
    char *response = response_parser();
    printf("%s\n", response);

    uint16_t status = http_response_status(response);
    printf("%lu\n", status);

    uint8_t headersLength;
    char *headersEnd;
    Header **headers = http_header_parser(response, &headersLength, &headersEnd);

    printf("%d\n", headersLength);
    for (uint8_t i = 0; i < headersLength; i++)
        printf("%s: %s\n", (*(headers + i))->key, (*(headers + i))->value);

    headersEnd++;
    Body *parsedBody = http_body_parser(headersEnd, headers, &headersLength);

    switch (parsedBody->content_type)
    {
    case HEADER_CONTENT_TYPE_TEXT_PLAIN:
        printf("%s\n", parsedBody->data.data_text);
        break;
    case HEADER_CONTENT_TYPE_APPLICATION_JSON:
        display_json(parsedBody->data.data_json, parsedBody->data_size);
        break;
    }

    Header *headerFound = find_header(headers, headersLength, "date");
    printf("%s\n", headerFound->value);
    time_t currentTime = parse_date(headerFound->value);
    printf("%lli\n", currentTime);
}