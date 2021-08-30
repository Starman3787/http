#include <stdlib.h>
#include <stdio.h>
#include "../../http_body_parser/http_body_structures.h"
#include "http_function_declarations.h"

void free_body(Body **parsedBody)
{
    switch ((*parsedBody)->content_type)
    {
    case HEADER_CONTENT_TYPE_TEXT_PLAIN:
        puts("FREEING TEXT/PLAIN");
        free((*parsedBody)->data.data_text);
        break;
    case HEADER_CONTENT_TYPE_APPLICATION_JSON:
        puts("FREEING APPLICATION/JSON");
        free_json(&((*parsedBody)->data.data_json), (*parsedBody)->data_size);
        break;
    }
    free(*parsedBody);
}