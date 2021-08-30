#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "../http_header_parser/http_header_structures.h"
#include "./http_body_structures.h"
#include "../util/to_lower_case/to_lower_case.h"
#include "http_function_declarations.h"

Body *http_body_parser(char *rawBody, Header **headers, uint8_t headersLength)
{
    Body *parsedBody;
    if ((parsedBody = malloc(sizeof(Body) * 1)) == NULL)
        return NULL;
    Header *transferEncodingHeader = find_header(headers, headersLength, "transfer-encoding");
    if (transferEncodingHeader->value == NULL)
    {
        // transfer-encoding header not present
    }
    else
    {
        uint8_t transferEncodingValuesCount;
        char **transferEncodingHeaderValues = split_header_values(transferEncodingHeader->value, &transferEncodingValuesCount, ',');
        size_t bodySize = 0;
        for (uint8_t i = 0; i < transferEncodingValuesCount; i++)
            to_lower_case(*(transferEncodingHeaderValues + i));
        while (transferEncodingValuesCount--)
        {
            if (strcmp(*(transferEncodingHeaderValues + transferEncodingValuesCount), "chunked") == 0)
            {
                rawBody = chunked(rawBody, &bodySize);
                free(*(transferEncodingHeaderValues + transferEncodingValuesCount));
            }
        }
    }
    Header *contentTypeHeader = find_header(headers, headersLength, "content-type");
    uint8_t contentTypeValuesCount;
    char **contentTypeHeaderValues = split_header_values(contentTypeHeader->value, &contentTypeValuesCount, ';');
    if (strcmp(*contentTypeHeaderValues, "application/json") == 0)
    {
        size_t json_size;
        parsedBody->content_type = HEADER_CONTENT_TYPE_APPLICATION_JSON;
        parsedBody->data.data_json = parse_json(rawBody, &json_size);
        parsedBody->data_size = json_size;
    }
    else if (strcmp(*contentTypeHeaderValues, "text/plain") == 0)
    {
        parsedBody->content_type = HEADER_CONTENT_TYPE_TEXT_PLAIN;
        parsedBody->data.data_text = rawBody;
        parsedBody->data_size = strlen(rawBody) + 1;
    }
    while (contentTypeValuesCount--)
        free(*(contentTypeHeaderValues + contentTypeValuesCount));
    return parsedBody;
}