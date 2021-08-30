#include <stdio.h>
#include "../../http_body_parser/http_body_structures.h"
#include "http_function_declarations.h"
#ifdef DMALLOC
#include "dmalloc.h"
#endif

void display_body(Body *parsedBody)
{
    switch (parsedBody->content_type)
    {
    case HEADER_CONTENT_TYPE_TEXT_PLAIN:
        printf("VALUE: %s\n", parsedBody->data.data_text);
        break;
    case HEADER_CONTENT_TYPE_APPLICATION_JSON:
        display_json(parsedBody->data.data_json, parsedBody->data_size);
        break;
    }
}